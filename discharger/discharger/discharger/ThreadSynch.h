
#pragma once

#include <atomic>
#include <QObject>

/**
* Klasa odpowiedzialna za synchronizacjê w¹tków gui oraz wykonuj¹cego czasoch³onne zadanie.
*/
class ThreadSynch : public QObject
{
	Q_OBJECT

public:

	/** Metoda zwracaj¹ca status w¹tku pracuj¹cego.
	* @return true - pracuje, false - praca zakoñczona.
	*/
	bool running() const { return state; }

	/** Metoda zwracaj¹ca czy w¹tek pracuj¹cy zacz¹³ pracê.
	* @return Czy w¹tek zacz¹³ pracê, true - tak.
	*/
	bool started()	const { return state ? true : false; };

	/** Metoda zwracaj¹ca czy w¹tek pracuj¹cy zakoñczy³ pracê.
	* @return Czy w¹tek zakoñczy³ pracê, true - tak.
	*/
	bool finished()	const { return state ? false : true; };

public slots:
	/** Slot emituj¹cy sygna³ pocz¹tku pracy.
	*/
	void start() { change(true); };

	/** Slot emituj¹cy sygna³ koñca pracy.
	*/
	void stop() { change(false); };

signals:
	/** Sygna³ zmiany statusu w¹tku pracuj¹cego.
	*/
	void changed();

private:
	std::atomic<bool> state = false;

	void change(bool b) {
		if (state != b) {
			state = b;
			emit changed();
		}
	}
};