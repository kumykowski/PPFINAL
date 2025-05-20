#include "movie.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <limits>

#include <windows.h>

using namespace MovieOrganizer;

int main(int argc, char* argv[]) {
    // TO CHAT ROBIL Z TYMI POLSKIMI ZNAKAMI
    SetConsoleOutputCP(CP_UTF8);
    
    MovieCollection movies;
    std::string defaultFilename = "movies.txt";
    
    if (argc > 1) {
        defaultFilename = argv[1];
        if (!loadMoviesFromFile(movies, defaultFilename)) {
            std::cout << "Nie można załadować pliku: " << defaultFilename << std::endl;
            std::cout << "Rozpoczynanie z pustą kolekcją." << std::endl;
        }

    }
    
    int choice = -1;
    while (choice != 0) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: {
                Title title;
                Genre genre;
                Year year;
                Rating rating;
                
                std::cout << "Podaj tytuł filmu: ";
                std::getline(std::cin, title);
                
                std::cout << "Podaj gatunek filmu: ";
                std::getline(std::cin, genre);
                
                std::cout << "Podaj rok produkcji: ";
                std::string yearStr;
                while (true) {
                    std::cin >> yearStr;
                    bool isValidYear = true;
                    for (char const &c : yearStr) {
                        if (std::isdigit(c) == 0) {
                            isValidYear = false;
                            break;
                        }
                    }
                    if (isValidYear) {
                        try {
                            year = std::stoi(yearStr);
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                            break;
                        } catch (const std::out_of_range& oor) {
                            std::cout << "Rok produkcji jest za duży. Podaj poprawny rok: ";
                        } catch (const std::invalid_argument& ia) {
                            //TUTAJ Z MARCELEM GOTOWAŁEM ZEBY MIEC TA WALIDACJE DATY DZIEKI MARCELEK PAN PRZYMNKNIE OCZKO :3
                            std::cout << "Nieprawidłowy format roku. Podaj poprawny rok: ";
                        }
                    } else {
                        std::cout << "Nieprawidłowy format roku. Rok musi być liczbą. Podaj poprawny rok: ";
                    }
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                }
                
                std::cout << "Podaj ocenę filmu (1-10): ";
                std::cin >> rating;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                movies.push_back(createMovie(title, genre, year, rating));
                std::cout << "Film został dodany pomyślnie." << std::endl;
                break;
            }
            case 2:
                displayAllMovies(movies);
                break;
            case 3: {
                Title searchTitle;
                std::cout << "Podaj tytuł filmu do wyszukania: ";
                std::getline(std::cin, searchTitle);
                
                int index = findMovieByTitle(movies, searchTitle);
                if (index != NOT_FOUND) {
                    std::cout << "\nZnaleziono film:" << std::endl;
                    displayMovie(movies[index]);
                } else {
                    std::cout << "Nie znaleziono filmu." << std::endl;
                }
                break;
            }
            case 4: {
                if (movies.empty()) {
                    std::cout << "Brak filmów do posortowania." << std::endl;
                    break;
                }
                
                bubbleSortMovies(movies);
                std::cout << "Filmy posortowane według oceny." << std::endl;
                break;
            }
            case 5: {
                Title removeTitle;
                std::cout << "Podaj tytuł filmu do usunięcia: ";
                std::getline(std::cin, removeTitle);
                
                int index = findMovieByTitle(movies, removeTitle);
                if (index != NOT_FOUND) {
                    removeMovie(movies, index);
                    std::cout << "Film został pomyślnie usunięty." << std::endl;
                } else {
                    std::cout << "Nie znaleziono filmu." << std::endl;
                }
                break;
            }
            case 6: {
                std::string filename;
                std::cout << "Podaj nazwę pliku do zapisu: ";
                std::cin >> filename;
                
                if (saveMoviesToFile(movies, filename)) {
                    std::cout << "Filmy zapisane do pliku pomyślnie." << std::endl;
                } else {
                    std::cout << "Błąd podczas zapisywania do pliku." << std::endl;
                }
                break;
            }
            case 7: {
                std::string filename;
                std::cout << "Podaj nazwę pliku do wczytania: ";
                std::cin >> filename;
                
                if (loadMoviesFromFile(movies, filename)) {
                
                } else {
                    std::cout << "Błąd podczas wczytywania pliku." << std::endl;
                }
                break;
            }
            case 8: {
                displayStatistics(movies);
                break;
            }
            case 0:
                std::cout << "eloooo" << std::endl;
                break;
            default:
                std::cout << "zla opcja" << std::endl;
        }
    }
    
    return SUCCESS;
}