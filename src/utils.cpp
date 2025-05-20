#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

namespace MovieOrganizer {

void displayMenu() {
    std::cout << "\n---- Organizator Filmów ----" << std::endl;
    std::cout << "1. Dodaj nowy film" << std::endl;
    std::cout << "2. Wyświetl wszystkie filmy" << std::endl;
    std::cout << "3. Wyszukaj film" << std::endl;
    std::cout << "4. Sortuj filmy według oceny" << std::endl;
    std::cout << "5. Usuń film" << std::endl;
    std::cout << "6. Zapisz filmy do pliku" << std::endl;
    std::cout << "7. Wczytaj filmy z pliku" << std::endl;
    std::cout << "8. Wyświetl statystyki" << std::endl;
    std::cout << "0. Wyjście" << std::endl;
    std::cout << "Wybierz opcję: ";
}

void displayAllMovies(const MovieCollection& movies) {
    if (movies.empty()) {
        std::cout << "Brak filmów w kolekcji." << std::endl;
        return;
    }
    
    std::cout << "\n---- Kolekcja Filmów ----" << std::endl;
    for (size_t i = 0; i < movies.size(); i++) {
        std::cout << "\nFilm #" << (i + 1) << std::endl;
        displayMovie(movies[i]);
        std::cout << "------------------------" << std::endl;
    }
}

int findMovieByTitle(const MovieCollection& movies, const Title& title) {
    for (size_t i = 0; i < movies.size(); i++) {
        if (movies[i].title == title) {
            return i;
        }
    }
    return NOT_FOUND;
}

void bubbleSortMovies(MovieCollection& movies) {
    for (size_t i = 0; i < movies.size() - 1; i++) {
        for (size_t j = 0; j < movies.size() - i - 1; j++) {
            if (movies[j].rating < movies[j + 1].rating) {
                Movie temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
}

void removeMovie(MovieCollection& movies, int index) {
    if (index >= 0 && static_cast<size_t>(index) < movies.size()) {
        movies.erase(movies.begin() + index);
    }
}

bool saveMoviesToFile(const MovieCollection& movies, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    for (const Movie& movie : movies) {
        file << movie.title << "," << movie.genre << "," << movie.year << "," << movie.rating << std::endl;
    }
    
    file.close();
    std::cout << "Zapisano " << movies.size() << " filmów do pliku." << std::endl;
    return true;
}

bool loadMoviesFromFile(MovieCollection& movies, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    size_t initialSize = movies.size();
    std::string line, title, genre, yearStr, ratingStr;
    
    while (std::getline(file, line)) { //getline zaproponował mi marcelek mam nadzieje ze to bedzie git bo to fajne jest 
        std::stringstream ss(line);
        
        if (std::getline(ss, title, ',') && 
            std::getline(ss, genre, ',') && 
            std::getline(ss, yearStr, ',') && 
            std::getline(ss, ratingStr)) {
            
            try {
                int year = std::stoi(yearStr);
                float rating = std::stof(ratingStr);
                movies.push_back(createMovie(title, genre, year, rating));
            }
            catch (const std::exception& e) {
                std::cerr << "Błąd podczas konwersji danych: " << e.what() << std::endl;
        
            }
        } else {
            std::cerr << "Pominięto nieprawidłową linię: " << line << std::endl;
        }
    }
    
    file.close();
    std::cout << "Dodano " << movies.size() - initialSize << " nowych filmów." << std::endl;
    return true;
}

void displayStatistics(const MovieCollection& movies) {
    if (movies.empty()) {
        std::cout << "Brak filmów w kolekcji." << std::endl;
        return;
    }
    
    float totalRating = 0;
    for (const Movie& movie : movies) {
        totalRating += movie.rating;
    }
    
    float averageRating = totalRating / movies.size();
    
    std::cout << "\n---- Statystyki Filmów ----" << std::endl;
    std::cout << "Całkowita liczba filmów: " << movies.size() << std::endl;
    std::cout << "Średnia ocena: " << averageRating << "/10" << std::endl;
}

}