#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>

#define MAX_RATING 10
#define MIN_RATING 1
#define DEFAULT_RATING 5

namespace MovieOrganizer {

typedef std::string Title;
typedef std::string Genre;
typedef int Year;
typedef float Rating;

struct Movie {
    Title title;
    Genre genre;
    Year year;
    Rating rating;
};

void displayMovie(const Movie& movie);
Movie createMovie(const Title& title, const Genre& genre, Year year, Rating rating);
bool compareByRating(const Movie& movie1, const Movie& movie2);

}

#endif