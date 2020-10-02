SELECT people.name FROM people WHERE people.id IN --select the names
(SELECT stars.person_id FROM stars WHERE stars.movie_id IN --From a set of movies
(SELECT stars.movie_id FROM stars WHERE stars.person_id IN --In which such movies
(SELECT people.id FROM people WHERE people.name = "Kevin Bacon" AND people.birth = 1958))) --Kevin Bacon is also included.
AND people.name != "Kevin Bacon" --Kevin Bacon Exempted.
GROUP BY people.id; --Remove Duplicates in case.
