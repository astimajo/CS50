SELECT name FROM people, directors, ratings WHERE people.id = directors.person_id AND directors.movie_id = ratings.movie_id AND rating >= 9 GROUP BY people.id;

