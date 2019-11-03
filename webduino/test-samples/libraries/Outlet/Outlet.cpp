/*
  Outlet.h - Utils for the Outlet object definition
  Author: Ralph Florent
  Created on October 29, 2019
*/

#include "Arduino.h"
#include "Outlet.h"

Outlet::Outlet() {
	_id = 0;
	_state = false;
	_scheduled = "";
	_description = "Outlet ";
}

Outlet::Outlet(char id, boolean state) {
	_id = id;
	_state = state;
	_description = "Outlet ";
	//_description += id;
}

void Outlet::begin() {
	pinMode(_id, OUTPUT);
	digitalWrite(_id, HIGH);
}

void Outlet::turnOn() {
	if(_id > 0){
		digitalWrite(_id, LOW);
		_state = true;
	}
}

void Outlet::turnOff() {
	if(_id > 0){
		digitalWrite(_id, HIGH);
		_state = false;
	}
}


void Outlet::setId(char id) {
	_id = id;
}

void Outlet::setState(boolean state) {
	_state = state;
}

void Outlet::setScheduled(String scheduled) {
	_scheduled = scheduled;
}

void Outlet::setDescription(String description) {
	_description = description;
}

char Outlet::getId() {
	return _id;
}

boolean Outlet::getState() {
	return _state;
}

String Outlet::getScheduled() {
	return _scheduled;
}

String Outlet::getDescription() {
	return _description;
}
