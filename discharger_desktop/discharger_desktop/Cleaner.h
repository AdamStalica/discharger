#pragma once
#include <QLineEdit>
#include <QComboBox>
#include <QProgressBar>
#include <QLabel>
#include <QTextBrowser>
#include <QTreeWidget>

class Cleaner {
public:
	template<class T>
	static void clearChildrens(QObject * parent, const QString & regex = QString());
};

template<class T>
inline void Cleaner::clearChildrens(QObject * parent, const QString & regex) {}

template<>
inline void Cleaner::clearChildrens<QLineEdit>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QLineEdit *>(QRegularExpression(regex))) {
		obj->setText("");
	}
}

template<>
inline void Cleaner::clearChildrens<QComboBox>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QComboBox *>(QRegularExpression(regex))) {
		obj->clear();
		obj->setCurrentIndex(-1);
	}
}

template<>
inline void Cleaner::clearChildrens<QProgressBar>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QProgressBar *>(QRegularExpression(regex))) {
		obj->reset();
	}
}

template<>
inline void Cleaner::clearChildrens<QLabel>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QLabel *>(QRegularExpression(regex))) {
		obj->setText("");
	}
}

template<>
inline void Cleaner::clearChildrens<QTextBrowser>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QTextBrowser *>(QRegularExpression(regex))) {
		obj->setText("");
	}
}

template<>
inline void Cleaner::clearChildrens<QTreeWidget>(QObject * parent, const QString & regex) {
	for (auto obj : parent->findChildren<QTreeWidget *>(QRegularExpression(regex))) {
		obj->clear();
	}
}