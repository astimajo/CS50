SELECT movies.title FROM people, movies, ratings, stars WHERE movies.id = ratings.movie_id AND people.id = stars.person_id AND stars.movie_id = movies.id AND people.name = 'Chadwick Boseman' ORDER BY ratings.rating DESC LIMIT 5;

