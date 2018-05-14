//
// Created by buran on 17/04/18.
//

#include <MakeRequest_Impl.h>

#include <RequestParams.h>
#include <TwitchException.h>
#include <Log.h>

namespace TwitchXX
{
/**
*****************************************************************************************
*  @brief      MakreRequest main method
*
*  @details      Performs request to Twitch service
*
*  @param      params MakeRequest::ReqiestParams object - request descriptor
*
*  @return     resposne parsed to web::json::value object. Null-json if return code != OK.
*			   Updates last status_code field.
****************************************************************************************/
    web::json::value MakeRequest_Impl::performRequest(const RequestParams &params)
    {
        web::http::client::http_client http_client("https://api.twitch.tv/", _config);
        web::http::http_request request(params.method);

        if(_client_id.length() > 0)request.headers().add("Client-ID", _client_id);
        if(params.scope != AuthScope::NO_SCOPE)
        {
            if(!_authToken)
            {
                std::stringstream ss;
                ss << "No auth token provided for " << params.uri.to_string() << " request";
                Log::Error(ss.str());
                throw TwitchException(ss.str().c_str());
            }
            request.headers().add("Authorization", _authToken->get(params.scope));
        }
        request.set_request_uri({params.uri});
        request.headers().set_content_type("application/json");
        if (!params.body.is_null())
        {
            utility::stringstream_t ss;
            ss << params.body;
            request.set_body(ss.str());
            //request.headers().set_content_type(U("application/json"));
        }

        _response_header_params.clear();
        if(params.responseHeadersParams.size())
        {
            std::for_each(params.responseHeadersParams.begin(),
                          params.responseHeadersParams.end(),
            [&](const std::string& key)
                          {
                              _response_header_params.insert({key, std::string()});
                          });
        }

        Log::Debug("Request: " + request.to_string());

        pplx::task<web::json::value> task = http_client.request(request)
                .then([this](web::http::http_response response) -> pplx::task<web::json::value>
                      {
                          Log::Debug("Response: " + response.to_string());
                          Log::Info("Response status: " + response.status_code());
                          fetchHeaderParams(response.headers());
                          this->_last_status = response.status_code();
                          if (response.status_code() == web::http::status_codes::OK
                              || response.status_code() == web::http::status_codes::Accepted)
                          {
                              if (response.headers().content_type().find("json") == std::wstring::npos)
                              {
                                  return response.extract_json(true);
                              }


                              return response.extract_json();

                          }
                          else
                          {
                              auto error = response.extract_json().get();
                              utility::string_t msg;
                              if (!error.is_null())
                              {
                                  msg = error.at("error").as_string() + ": " + error.at("message").as_string();
                              }
                              Log::Error("Request returned an error: " + msg);

                              throw TwitchException(msg, response.status_code());
                          }
                      });

        try
        {
            auto result = task.get();
            if (params.callback != nullptr)
            {
                Log::Debug("Calling a callback");
                params.callback(result);
            }
            return result;
        }
        catch (const std::exception& e)
        {
            Log::Error(std::string("Unknown exception: ") + e.what());
            throw;
        }
    }

    MakeRequest_Impl::MakeRequest_Impl(const options &opt)
    {
        try
        {
            _client_id = opt.at("api_key");
        }
        catch (const std::out_of_range&)
        {
            utility::stringstream_t ss;
            ss << __FUNCTION__ << ": Not enough parameters!"
               << " api_key=" << _client_id;
            Log::Error(ss.str());
            throw std::invalid_argument(ss.str());
        }

        setupProxy(opt);
    }

    void MakeRequest_Impl::fetchHeaderParams(web::http::http_headers &headers)
    {
        std::for_each(_response_header_params.begin(), _response_header_params.end(), [&](auto& p)
        {
            if(headers.has(p.first))
            {
                p.second = headers[p.first];
            } else
            {
                p.second = {};
            }
        });
    }

    /**
*****************************************************************************************
*  @brief      Setup proxy.
*
*  @details    SetupProxy() requires options to be defined and filled
*			   with values (proxy & proxy_password).
*			   Note: Proxy host must starts with connection scheme (i.e. http,https etc).
*  @param      options options dictionary (must contain proxy and/or proxy_password)
*              proxy hostname shoudl start with a scheme - http, https etc.
*
*  @return     throws std::runtime_error if proxy settings not present in Options
****************************************************************************************/
    void MakeRequest_Impl::setupProxy(const std::map<utility::string_t, utility::string_t> &options)
    {
        //Check global Options object for proxy settings;
        if (options.find("proxy") != options.end())
        {
            Log::Debug("Proxy settings found!");
            web::web_proxy proxy(options.at("proxy"));
            //Check that both login and password were found in the options.
            if (options.find("proxy_user") != options.end()
                && options.find("proxy_password") != options.end())
            {
                web::credentials credentials(options.at("proxy_user"),
                                             options.at("proxy_password"));
                proxy.set_credentials(credentials);
            }
            _config.set_proxy(proxy);
        }
    }

    void MakeRequest_Impl::setAuthToken(const std::shared_ptr<AuthToken> &token)
    {
        Log::Debug("Setting an auth token: " + token->tokenType());
        _authToken = token;
    }


}