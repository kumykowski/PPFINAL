#include "movie.hpp"
#include <iostream>

namespace MovieOrganizer {

void displayMovie(const Movie& movie) {
    std::cout << "Tytuł: " << movie.title << std::endl;
    std::cout << "Gatunek: " << movie.genre << std::endl;
    std::cout << "Rok: " << movie.year << std::endl;
    std::cout << "Ocena: " << movie.rating << "/10" << std::endl;
}

Movie createMovie(const Title& title, const Genre& genre, Year year, Rating rating) {
    Movie movie;
    movie.title = title;
    movie.genre = genre;
    movie.year = year;
    
    if (rating < MIN_RATING) {
        movie.rating = MIN_RATING;
    } else if (rating > MAX_RATING) {
        movie.rating = MAX_RATING;
    } else {
        movie.rating = rating;
    }
    
    return movie;
}

bool compareByRating(const Movie& movie1, const Movie& movie2) {
    return movie1.rating > movie2.rating;
}

}