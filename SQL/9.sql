SELECT name FROM people, stars, movies WHERE people.id = stars.person_id AND stars.movie_id = movies.id AND year = '2004' GROUP BY people.id ORDER BY birth ASC;
