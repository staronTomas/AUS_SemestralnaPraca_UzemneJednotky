#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "structures/list/linked_list.h"
#include "structures/heap_monitor.h"



class ZoznamUzemnychJednotiek {

private:
	
	structures::LinkedList<structures::LinkedList<std::string>*>* zoznamObci_;

	structures::LinkedList<structures::LinkedList<std::string>*>* zoznamOkresov_;

	structures::LinkedList<structures::LinkedList<std::string>*>* zoznamKrajov_;

public:

	ZoznamUzemnychJednotiek() {
		
		zoznamObci_ = new structures::LinkedList<structures::LinkedList<std::string>*>;

		zoznamOkresov_ = new structures::LinkedList<structures::LinkedList<std::string>*>;

		zoznamKrajov_ = new structures::LinkedList<structures::LinkedList<std::string>*>;;
	};
	~ZoznamUzemnychJednotiek() {};


	//gettery

	structures::LinkedList<structures::LinkedList<std::string>*>* getZoznamObci() {
		return zoznamObci_;
	}
	structures::LinkedList<structures::LinkedList<std::string>*>* getZoznamOkresov() {
		return zoznamOkresov_;
	}
	structures::LinkedList<structures::LinkedList<std::string>*>* getZoznamKrajov() {
		return zoznamKrajov_;
	}


	// settery

	void setZoznamObci(structures::LinkedList<structures::LinkedList<std::string>*>* zoznamObci) {
		zoznamObci_ = zoznamObci;
	}
	void setZoznamOkresov(structures::LinkedList<structures::LinkedList<std::string>*>* zoznamOkresov) {
		zoznamOkresov_ = zoznamOkresov;
	}
	void setZoznamKrajov(structures::LinkedList<structures::LinkedList<std::string>*>* zoznamKrajov) {
		zoznamKrajov_ = zoznamKrajov;
	}


};