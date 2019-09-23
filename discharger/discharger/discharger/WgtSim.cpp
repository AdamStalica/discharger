#include "WgtSim.h"
#include <QRegExpValidator>

using json = nlohmann::json;

WgtSim::WgtSim(ApiHolder * api, BasicData * data, WgtLoader * loader, QWidget *parent)
	:	QWidget(parent),	
		api(api),
		data(data),
		loader(loader)
{
	ui.setupUi(this);



	connect(ui.back_btn, &QPushButton::clicked, this, [this]() {
		emit finished();
	});

	ui.set_temp_ln->setValidator(new QRegExpValidator(QRegExp("-?\\d+\\.?\\d+"), this));
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
