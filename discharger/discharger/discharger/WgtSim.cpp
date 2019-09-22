#include "WgtSim.h"

using json = nlohmann::json;

WgtSim::WgtSim(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent)
	:	QWidget(parent),	
		api(api),
		data(data),
		loader(loader)
{
	ui.setupUi(this);



}

void WgtSim::setUartHolder(UartHolder * uart)
{
	this->uart = uart;
}

void WgtSim::setBasicSimData(const json & data)
{
}

WgtSim::~WgtSim()
{
}
