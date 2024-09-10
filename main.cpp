#include <iostream>
#include <Windows.h>
#include <stdlib.h>

#include "Controller.hpp"
#include "Config.hpp"
#include "DbConnection.hpp"
#include "FileManagement.hpp"

// Compart la primes des assurances maladie
// 
// *** Les primes *** //
//
// La prime maladie est le montant que vous devez verser chaque mois
//  � votre caisse-maladie.
// 
// Ce montant d�pend de la caisse � laquelle vous �tes affili�,
//  de la franchise et du mod�le d�assurance choisis ainsi que de votre lieu de domicile.
// Les enfants et les jeunes de moins de 25 ans b�n�ficient de primes plus basses.


// *** La franchise *** //
// 
// La franchise est le montant que vous devez payer vous-m�me chaque
//	ann�e � titre de participation aux co�ts.Ce n�est qu�une fois ce
//	montant atteint que votre caisse-maladie prendra le relai.
// La franchise minimale des adultes est de 300 francs, la plus haute,
//	de 2500 francs; pour les enfants, la franchise se situe entre 0 et 600 francs.
// 
// Un exemple : la franchise que vous avez choisie est de 300 francs et 
//	vous devez vous rendre deux fois chez le m�decin. Celui-ci facture 
//	chaque visite 200 francs.Vous payez la premi�re facture, plus 100 francs de la seconde;
//	la caisse-maladie prend en charge les 100 francs restants � moins 10 francs de quote-part
//	ainsi que toutes les autres factures de l�ann�e en cours.


// *** La quote-part *** //
// 
// Une fois la franchise atteinte, 
//	vous ne payez plus qu�une quote-part de 10 % des frais,
//	plafonn�e � 700 francs par an(350 francs pour les enfants).
// Votre participation maximale aux frais s��l�ve donc au montant de votre franchise, 
//	auquel s�ajoutent 700 francs de quote-part.


int main(int argc, char* argv[]){

#if DEBUG
    std::cout << "DEBUG mode true\n";
    //std::string path{ "C:\\Users\\ThJo\\source\\repos\\ComparatifAssuranceMaladie\\x64\\Release\\2024_Canton.VD.csv" };
    std::string path{ "C:\\Users\\ThJo\\source\\repos\\ComparatifAssuranceMaladie\\x64\\Release\\2024_Test.csv" }; // Simple CSV
#else 
    std::cout << "DEBUG mode false\n";
    std::string path{ "" };
#endif // DEBUG

    ctrl::createNewDatabase();

    ext::CsvRead file;
    ext::CsvWrite insert_DB;
    insert_DB.showParsing(file.csvReader(path, argc, argv));
    insert_DB.createHeathInsurance(file.csvReader(path, argc, argv));

    ctrl::displayDatabase();

    
	return 0;
}
