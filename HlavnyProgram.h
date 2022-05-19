#pragma once


#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "enum_UzemnaJednotka.h"
#include "enum_VyssiCelok.h"
#include "enum_TypVzdelania.h"
#include "enum_Pohlavie.h"
#include "enum_EVS.h"
#include "structures/list/linked_list.h"


#include "structures/heap_monitor.h"

#include "UzemnaJednotka.h"
#include "CsvReader.h"


class HlavnyProgam {
	


private:

	UzemnaJednotka* slovensko_;
	CsvReader* reader_;

public:

	HlavnyProgam() {
		slovensko_ = new UzemnaJednotka("Slovensko", UZEMNA_JEDNOTKA::STAT, "SK", nullptr);
		reader_ = new CsvReader();

	}

	~HlavnyProgam() {

	}


	void spustiProgram() {
		std::cout << "### Ahoj, Vitaj v tomto programe ###" << std::endl << std::endl;
		Sleep(1500);
		system("CLS");
		nacitajVsetkyData();
	}


	void nacitajVsetkyData() {
		
		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: obce.csv" << std::endl;
		std::cout << "# Hotovo -> 0%" << std::endl;
		LinkedList<LinkedList<std::string>*>* zoznamObci = reader_->nacitajObce("data_bez_diakritiky/obce.csv");  // Obce mi nacita:   NazovUJ;KodUJ

		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: okresy.csv" << std::endl;
		std::cout << "# Hotovo -> 20%" << std::endl;
		LinkedList<LinkedList<std::string>*>* zoznamOkresov = reader_->nacitajOkresy("data_bez_diakritiky/okresy.csv");  // okresy mi nacita:   NazovUJ;KodUJ

		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: kraje.csv" << std::endl;
		std::cout << "# Hotovo -> 40%" << std::endl;
		LinkedList<LinkedList<std::string>*>* zoznamKrajov = reader_->nacitajKraje("data_bez_diakritiky/kraje.csv");  // kraje mi nacita:   NazovUJ;KodUJ

		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: vzdelanie.csv" << std::endl;
		std::cout << "# Hotovo -> 60%" << std::endl;
		SortedSequenceTable<std::string, Vzdelanie*>* vzdelanieZoSuborov = reader_->nacitajVzdelanie("data_bez_diakritiky/vzdelanie.csv");

		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: vek.csv" << std::endl;
		std::cout << "# Hotovo -> 80%" << std::endl;
		SortedSequenceTable<std::string, Vek*>* vekZoSuborov = reader_->nacitajVek("data_bez_diakritiky/vek.csv");

		// Utriedenie duplicitnych zoznamov OBCI, priadnie na koniec nazov okresu v ktorom je

		system("cls");
		std::cout << "• Parsovanie bolo dokoncene." << std::endl;
		std::cout << std::endl;
		std::cout << "• Hotovo -> 100%" << std::endl;
		Sleep(1000);

		for (int i = 0; i < zoznamKrajov->size(); i++)
		{
			std::string nazovUjKraj = zoznamKrajov->at(i)->at(0);
			std::string kodUjKraj = zoznamKrajov->at(i)->at(1);

			UzemnaJednotka* novyKraj = new UzemnaJednotka(nazovUjKraj, UZEMNA_JEDNOTKA::KRAJ, kodUjKraj, slovensko_);

			slovensko_->getUzemneJednotkyChildren()->insert(nazovUjKraj, novyKraj);

			system("CLS");
			int percentoDokoncene = 100 / zoznamKrajov->size() * i;
			std::cout << "# Prebieha vkladanie dat do uzemnych jednotiek." << std::endl;
			std::cout << "#" << std::endl;
			std::cout << "# Prebieha ukladanie dat v Uzemnej jednotke -> " << nazovUjKraj << " a jeho okresoch a obciach." << std::endl;
			std::cout << "# Dokoncene: " << percentoDokoncene << "%" << std::endl;

			for (int j = 0; j < zoznamOkresov->size(); j++)
			{
				std::string okresNazovUj = zoznamOkresov->at(j)->at(0);
				std::string okresKodUJ = zoznamOkresov->at(j)->at(1);

				std::string subKodUjOkres = okresKodUJ.substr(0,5);
				
				int porovnanie = subKodUjOkres.compare(kodUjKraj);

				if (porovnanie == 0)
				{
					// patri okres do tohoto kraja
					// idem okresu priradit jeho OBCE V CYKLE
					UzemnaJednotka* novyOkres = new UzemnaJednotka(okresNazovUj, UZEMNA_JEDNOTKA::OKRES, okresKodUJ, novyKraj);
					novyKraj->getUzemneJednotkyChildren()->insert(okresNazovUj, novyOkres);

					for (int j = 0; j < zoznamObci->size(); j++)
					{
						std::string obecNazovUj = zoznamObci->at(j)->at(0);
						std::string obecKodUJ = zoznamObci->at(j)->at(1);

						std::string subKodUjObec = obecKodUJ.substr(0, 6);

						int porovnanie = subKodUjObec.compare(okresKodUJ);

						if (porovnanie == 0)
						{   
							// patri okres do tohoto kraja
							// idem okresu priradit jeho OBCE V CYKLE
							UzemnaJednotka* novaObec = new UzemnaJednotka(obecNazovUj, UZEMNA_JEDNOTKA::OBEC, obecKodUJ, novyOkres);
							novyOkres->getUzemneJednotkyChildren()->insert(obecNazovUj, novaObec);


							if (vzdelanieZoSuborov->containsKey(obecKodUJ)) {
								Vzdelanie* vzd = vzdelanieZoSuborov->find(obecKodUJ);
								novaObec->setVzdelanie(vzd);
								novaObec->navysPocetObyvatelovZoVzdelania(vzd);

								novyOkres->getVzdelanie()->navysCelkovyPocetVzdelania(vzd);
								novyOkres->navysPocetObyvatelovZoVzdelania(vzd);

								novyKraj->getVzdelanie()->navysCelkovyPocetVzdelania(vzd);
								novyKraj->navysPocetObyvatelovZoVzdelania(vzd);

								slovensko_->getVzdelanie()->navysCelkovyPocetVzdelania(vzd);
								slovensko_->navysPocetObyvatelovZoVzdelania(vzd);
							}	


							if (vekZoSuborov->containsKey(obecKodUJ)) {
								Vek* vek = vekZoSuborov->find(obecKodUJ);
								novaObec->setVekObyvatelov(vek);
								novaObec->getVekObyvatelov()->navysPocetEvsSkupin(vek);

								novyOkres->getVekObyvatelov()->navysPocetVekCelkovo(vek);
								novyOkres->getVekObyvatelov()->navysPocetEvsSkupin(vek);

								novyKraj->getVekObyvatelov()->navysPocetVekCelkovo(vek);
								novyKraj->getVekObyvatelov()->navysPocetEvsSkupin(vek);

								slovensko_->getVekObyvatelov()->navysPocetVekCelkovo(vek);
								slovensko_->getVekObyvatelov()->navysPocetEvsSkupin(vek);
							}

						}
					}
				}
			}	
		}

		system("CLS");
		std::cout << "# Nacitavanie dat bolo uspesne dokoncene." << std::endl;
		Sleep(1000);
		std::cout << "# Pre pokracovanie stlac lubovolnu klavesu." << std::endl;
		system("pause");
	}




	UzemnaJednotka* getSlovensko() {
		return slovensko_;
	}

};
