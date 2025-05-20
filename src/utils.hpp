#ifndef UTILS_HPP
#define UTILS_HPP

#include "movie.hpp"
#include <vector>
#include <string>

#define FILE_ERROR 1
#define SUCCESS 0
#define NOT_FOUND -1

namespace MovieOrganizer {

typedef std::vector<Movie> MovieCollection;

void displayMenu();
void displayAllMovies(const MovieCollection& movies);
int findMovieByTitle(const MovieCollection& movies, const Title& title);
void bubbleSortMovies(MovieCollection& movies);
bool saveMoviesToFile(const MovieCollection& movies, const std::string& filename);
bool loadMoviesFromFile(MovieCollection& movies, const std::string& filename);
void displayStatistics(const MovieCollection& movies);
void removeMovie(MovieCollection& movies, int index);

}

#endif