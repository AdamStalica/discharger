
#pragma once

#include <atomic>
#include <QObject>

/**
* Klasa odpowiedzialna za synchronizacj� w�tk�w gui oraz wykonuj�cego czasoch�onne zadanie.
*/
class ThreadSynch : public QObject
{
	Q_OBJECT

public:

	/** Metoda zwracaj�ca status w�tku pracuj�cego.
	* @return true - pracuje, false - praca zako�czona.
	*/
	bool running() const { return state; }

	/** Metoda zwracaj�ca czy w�tek pracuj�cy zacz�� prac�.
	* @return Czy w�tek zacz�� prac�, true - tak.
	*/
	bool started()	const { return state ? true : false; };

	/** Metoda zwracaj�ca czy w�tek pracuj�cy zako�czy� prac�.
	* @return Czy w�tek zako�czy� prac�, true - tak.
	*/
	bool finished()	const { return state ? false : true; };

public slots:
	/** Slot emituj�cy sygna� pocz�tku pracy.
	*/
	void start() { change(true); };

	/** Slot emituj�cy sygna� ko�ca pracy.
	*/
	void stop() { change(false); };

signals:
	/** Sygna� zmiany statusu w�tku pracuj�cego.
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