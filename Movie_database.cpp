#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Movie {
    std::string title;
    int releaseYear;
    std::string director;
    std::string genre;
};

void saveToFile(const std::vector<Movie>& movies, const std::string& filename) {
    std::ofstream outFile(filename);
    for (const auto& movie : movies) {
        outFile << movie.title << "," << movie.releaseYear << "," << movie.director << "," << movie.genre << "\n";
    }
}

std::vector<Movie> loadFromFile(const std::string& filename) {
    std::vector<Movie> movies;
    std::ifstream inFile(filename);
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string title, director, genre;
        int releaseYear;
        std::getline(ss, title, ',');
        ss >> releaseYear;
        ss.ignore();
        std::getline(ss, director, ',');
        std::getline(ss, genre, ',');
        movies.push_back({title, releaseYear, director, genre});
    }
    return movies;
}

void addMovie(std::vector<Movie>& movies) {
    Movie newMovie;
    std::cout << "Enter movie title: ";
    std::cin.ignore();
    std::getline(std::cin, newMovie.title);
    std::cout << "Enter release year: ";
    std::cin >> newMovie.releaseYear;
    std::cin.ignore();
    std::cout << "Enter director: ";
    std::getline(std::cin, newMovie.director);
    std::cout << "Enter genre: ";
    std::getline(std::cin, newMovie.genre);
    movies.push_back(newMovie);
    std::cout << "Movie added successfully!" << std::endl;
}

void editMovie(std::vector<Movie>& movies) {
    std::string title;
    std::cout << "Enter the title of the movie to edit: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    for (auto& movie : movies) {
        if (movie.title == title) {
            std::cout << "Enter new release year: ";
            std::cin >> movie.releaseYear;
            std::cin.ignore();
            std::cout << "Enter new director: ";
            std::getline(std::cin, movie.director);
            std::cout << "Enter new genre: ";
            std::getline(std::cin, movie.genre);
            std::cout << "Movie edited successfully!" << std::endl;
            return;
        }
    }
    std::cout << "Movie not found." << std::endl;
}

void deleteMovie(std::vector<Movie>& movies) {
    std::string title;
    std::cout << "Enter the title of the movie to delete: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    auto it = std::remove_if(movies.begin(), movies.end(), [&](const Movie& movie) {
        return movie.title == title;
    });
    if (it != movies.end()) {
        movies.erase(it, movies.end());
        std::cout << "Movie deleted successfully!" << std::endl;
    } else {
        std::cout << "Movie not found." << std::endl;
    }
}

void searchMovies(const std::vector<Movie>& movies) {
    std::string title;
    std::cout << "Enter the title of the movie to search for: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    for (const auto& movie : movies) {
        if (movie.title == title) {
            std::cout << "Title: " << movie.title << "\n"
                      << "Release Year: " << movie.releaseYear << "\n"
                      << "Director: " << movie.director << "\n"
                      << "Genre: " << movie.genre << "\n";
            return;
        }
    }
    std::cout << "Movie not found." << std::endl;
}

void viewAllMovies(const std::vector<Movie>& movies) {
    if (movies.empty()) {
        std::cout << "No movies in the database." << std::endl;
        return;
    }
    for (const auto& movie : movies) {
        std::cout << "Title: " << movie.title << "\n"
                  << "Release Year: " << movie.releaseYear << "\n"
                  << "Director: " << movie.director << "\n"
                  << "Genre: " << movie.genre << "\n\n";
    }
}

int main() {
    std::vector<Movie> movies = loadFromFile("movies.txt");
    int choice;

    do {
        std::cout << "\nMovie Database Application" << std::endl;
        std::cout << "1. Add Movie" << std::endl;
        std::cout << "2. Edit Movie" << std::endl;
        std::cout << "3. Delete Movie" << std::endl;
        std::cout << "4. Search Movie" << std::endl;
        std::cout << "5. View All Movies" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addMovie(movies);
                saveToFile(movies, "movies.txt");
                break;
            case 2:
                editMovie(movies);
                saveToFile(movies, "movies.txt");
                break;
            case 3:
                deleteMovie(movies);
                saveToFile(movies, "movies.txt");
                break;
            case 4:
                searchMovies(movies);
                break;
            case 5:
                viewAllMovies(movies);
                break;
            case 6:
                std::cout << "Exiting the application." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
