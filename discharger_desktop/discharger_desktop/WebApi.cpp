#include "WebApi.h"

const std::string WebApi::API_URL = "";

WebApi::WebApi(QObject *parent)
	: QObject(parent)
{
	hi = "ok";
}

WebApi::~WebApi()
{}
