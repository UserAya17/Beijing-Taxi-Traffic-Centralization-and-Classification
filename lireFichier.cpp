#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip> 

struct TaxiData 
{
    std::string id;
    std::string date;
    double lat;
    double lon;
};

int main() 
{
    std::vector<TaxiData> taxiData;
    //std::vector<std::pair<double, double>> coordonnees; // pour stocker les coordonnées lat et lon
    int i = 1;
    std::stringstream ss;
    ss << "C:\\Users\\Aya\\Desktop\\Atelier\\Bouziri\\ProjetTaxi\\T-drive Taxi Trajectories\\release\\taxi_log_2008_by_id\\" << i << ".txt";
    std::ifstream file(ss.str());
    if (file.is_open()) 
    {
        std::string line;
        while (std::getline(file, line)) 
        {
            std::stringstream lineStream(line);
            TaxiData taxiEntry;
            std::string cell;
            std::getline(lineStream, taxiEntry.id, ',');
            std::getline(lineStream, taxiEntry.date, ',');
            std::getline(lineStream, cell, ',');
            taxiEntry.lat = std::stod(cell);
            std::getline(lineStream, cell);
            taxiEntry.lon = std::stod(cell);
            taxiData.push_back(taxiEntry);
            //coordonnees.push_back(std::make_pair(taxiEntry.lat, taxiEntry.lon));
        }
        file.close();
    }

    // Afficher les données
    for (const auto& taxiEntry : taxiData) 
    {
        std::cout << "ID: " << taxiEntry.id << ", Date: " << taxiEntry.date
            << ", Lat: " << std::fixed << std::setprecision(5) << taxiEntry.lat
            << ", Lon: " << std::fixed << std::setprecision(5) << taxiEntry.lon << std::endl;
    }

    // Ouvrir un fichier en écriture
    std::ofstream outFile("coordonnees33.json");

    // Vérifier si le fichier est ouvert avec succès
    if (outFile.is_open()) 
    {
        // Écrire les coordonnées dans le fichier au format JSON
        outFile << "[";
        for (size_t i = 0; i < taxiData.size(); ++i) 
        {
            const TaxiData& taxiEntry = taxiData[i];
            outFile << "{ \"id\": \"" << taxiEntry.id << "\", \"date\": \"" << taxiEntry.date
                    << "\", \"lat\": " << std::fixed << std::setprecision(5) << taxiEntry.lat
                    << ", \"lon\": " << std::fixed << std::setprecision(5) << taxiEntry.lon << " }";
            // Ajouter une virgule si ce n'est pas le dernier élément
            if (i != taxiData.size() - 1) 
            {
                outFile << ",";
            }
            outFile << std::endl;
        }
        outFile << "]";

        std::cout << "Les coordonnées ont été stockées dans le fichier coordonnees.json" << std::endl;

        // Fermer le fichier
        outFile.close();
    }
    else 
    {
        std::cerr << "Erreur lors de l'ouverture du fichier coordonnees.json" << std::endl;
    }

    return 0;
}
