SELECT movies.title FROM movies JOIN people ON people.id = stars.person_id JOIN stars ON stars.movie_id = movies.id WHERE people.name = "Johnny Depp" 
INTERSECT 
SELECT movies.title FROM movies JOIN people ON people.id = stars.person_id JOIN stars ON stars.movie_id = movies.id WHERE people.name = "Helena Bonham Carter";
