#!/bin/bash

sudo mysql -u root <<QUERY

USE test;

INSERT INTO user (login, password)
  VALUES
  ("alice", "alice"),
  ("andrew", "andrew"),
  ("oleg", "oleg"),
  ("antony", "antony");

INSERT INTO song (name, author, genre, duration, date)
  VALUES
  ("Nice Boi", "Eskimo Callboy", "metalcore", 159, "2019-11-01"),
  ("Hurricane", "Escimo Callboy", "metalcore", 221, "2019-11-01"),
  ("Black Files", "Ben Howard", "indie folk", 381, "2011-09-30"),
  ("Waiting for You", "Nick Cave & The Bad Seeds", "alternative rock", 234, "2019-10-04"),
  ("Hunger", "The Score", "alternative rock", 123, "2019-08-09"),
  ("Rush", "The Score", "alternative rock", 176, "2019-08-09"),
  ("In My Bones", "The Score", "alternative rock", 169, "2019-08-09"),
  ("Sweet Disposition", "The Temper Trap", "indie rock", 234, "2008-01-01"),
  ("Into My Arms", "Nick Cave & The Bad Seeds", "alternative rock", 256, "1997-03-02"),
  ("Bright Horses", "Nick Cave & The Bad Seeds", "alternative rock", 292, "2019-10-04"),
  ("O Children", "Nick Cave & The Bad Seeds", "alternative rock", 409, "2004-09-20"),
  ("Prey", "The Neighbourhood", "indie pop", 282, "2015-10-30"),
  ("Single", "The Neighbourhood", "indie pop", 262, "2015-10-30"),
  ("R.I.P. 2 My Youth", "The Neighbourhood", "indie pop", 205, "2015-10-30"),
  ("Paradise", "The Neighbourhood", "indie pop", 209, "2018-11-02"),
  ("Mr. Brightside", "The Killers", "alternative rock", 222, "2003-09-29"),
  ("The Man", "The Killers", "alternative rock", 248, "2017-09-22"),
  ("Моя душа", "Andro", "pop", 155, "2019-12-19"),
  ("nextstep", "lowlife", "R&B", 148, "2019-12-17"),
  ("Мишка", "Пошлая Молли feat. KATERINA", "pop", 158, "2019-12-19"),
  ("associate", "масло черного тмина", "hip-hop", 126, "2019-12-19"),
  ("Ready To Die", "EARTHGANG", "hip-hop", 198, "2019-09-01"),
  ("Angelic Hoodrat", "Kenny Mason", "rap", 172, "2019-12-17"),
  ("Мое любимое", "Елена Темникова", "pop", 234, "2019-12-19"),
  ("Напомни", "Скриптонит", "hip-hop", 201, "2019-12-24"),
  ("Поворот (ft. Niman)", "Скриптонит", "hip-hop", 244, "2019-12-24"),
  ("Ага, ну", "Скриптонит", "hip-hop", 187, "2019-12-24"),
  ("All I Want for Christmas Is You", "Mariah Carey", "christmas", 241, "2019-11-01"),
  ("Last Christmas", "Wham!", "pop", 398, "1984-12-20"),
  ("Let It Snow", "Frank Sinatra", "christmas", 156, "1957-01-01"),
  ("Jingle Bell Rock", "Bobby Helms", "christmas", 130, "1970-01-01"),
  ("This Christmas", "Oh Wonder", "christmas", 219, "2019-11-29"),
  ("Despacito", "Luis Fonsi", "latino pop", 227, "2017-01-12"),
  ("Memories", "Maroon 5", "pop", 193, "2019-09-20"),
  ("Gods", "Nothing But Thieves", "indie rock", 209, "2018-10-19"),
  ("You Know Me Too Well", "Nothing But Thieves", "indie rock", 233, "2018-10-19"),
  ("If I Get High", "Nothing But Thieves", "indie rock", 206, "2015-10-16"),
  ("I'm Not Made By Design", "Nothing But Thieves", "indie rock", 232, "2015-10-16"),
  ("Your Life", "Hollywood Undead", "rap-rock", 199, "2017-10-27"),
  ("Outside", "Hollywood Undead", "rap-rock", 283, "2013-01-08"),
  ("Undead", "Hollywood Undead", "rap-rock", 282, "2008-09-02"),
  ("Circles", "Hollywood Undead", "rap-rock", 208, "2008-09-02"),
  ("Young", "Hollywood Undead", "rap-rock", 196, "2008-09-02"),
  ("California", "Hollywood Undead", "rap-rock", 196, "2008-09-02"),
  ("Missing", "Seafret", "indie", 207, "2016-01-29"),
  ("Zombie", "Bad Wolves", "rock", 254, "2018-01-01"),
  ("Mess Is Mine", "Vance Joy", "indie", 223, "2014-10-02"),
  ("Kiss Me", "Ed Sheeran", "pop", 274, "2011-09-09"),
  ("Shape Of You", "Ed Sheeran", "pop", 232, "2017-02-23"),
  ("Photograph", "Ed Sheeran", "pop", 259, "2014-06-20"),
  ("Oh My Stars", "Andrew Belle", "pop", 302, "2010-02-23"),
  ("Pieces", "Andrew Belle", "pop", 241, "2013-08-20"),
  ("Intro", "The XX", "indie-pop", 127, "2009-08-14"),
  ("Famous Last Words", "My Chemical Romance", "alternative rock", 298, "2006-10-23"),
  ("The Ghost of You", "My Chemical Romance", "alternative rock", 237, "2004-06-08"),
  ("Demons", "Imagine Dragons", "pop-rock", 175, "2012-02-14"),
  ("Radioactive", "Imagine Dragons", "pop-rock", 187, "2012-02-14"),
  ("Round and Round", "Imagine Dragons", "pop-rock", 162, "2012-02-14"),
  ("Numb", "Linkin Park", "alternative rock", 186, "2003-03-25"),
  ("New Divide", "Linkin Park", "alternative rock", 250, "2009-05-18"),
  ("What I've Done", "Linkin Park", "alternative rock", 205, "2007-04-02"),
  ("Boulevard Of Broken Dreams", "Green Day", "alternative rock", 258, "2004-09-20"),
  ("Will of the Scribes", "Darren Korb", "games", 179, "2017-07-25"),
  ("Wildfire", "Fatal Force & Crusher P", "games", 307, "2015-05-02"),
  ("Gone Forever", "Three Days Grace", "alternative rock", 221, "2006-06-13"),
  ("Over And Over", "Three Days Grace", "alternative rock", 192, "2006-06-13"),
  ("Last To Know", "Three Days Grace", "alternative rock", 207, "2009-09-22"),
  ("Head Above Water", "Theory Of A Deadman", "alternative rock", 213, "2011-06-07"),
  ("Santa Monica", "Theory Of A Deadman", "alternative rock", 246, "2005-03-29"),
  ("Not Meant To Be", "Theory Of A Deadman", "alternative rock", 215, "2008-04-01"),
  ("Satellite", "Starset", "alternative rock", 239, "2017-01-20"),
  ("Monster", "Starset", "alternative rock", 256, "2017-01-20"),
  ("Not The Only One", "Papa Roach", "alternative rock", 205, "2019-01-18"),
  ("Воздушный шар", "Сплин", "alternative rock", 206, "2019-12-20"),
  ("Тайком", "Сплин", "alternative rock", 225, "2019-12-20");

 INSERT INTO like_dislike (user_id, song_id, value)
   VALUES
   (1, 1, true),
   (1, 2, true),
   (1, 5, true),
   (1, 6, true),
   (1, 7, true),
   (1, 9, true),
   (1, 11, true),
   (1, 41, true),
   (1, 42, true),
   (1, 43, true),
   (1, 47, true),
   (1, 53, true),
   (1, 68, true),
   (1, 69, true),
   (1, 70, true),
   (1, 20, false),
   (1, 21, false),
   (1, 22, false),
   (1, 23, false),
   (1, 25, false),
   (1, 26, false),
   (2, 26, true),
   (2, 27, true),
   (2, 28, true),
   (2, 29, true),
   (2, 30, true),
   (2, 31, true),
   (2, 1, true),
   (2, 2, true),
   (2, 5, true),
   (2, 54, false),
   (2, 55, false),
   (2, 56, false),
   (2, 57, false),
   (2, 70, false),
   (2, 55, false),
   (3, 54, true),
   (3, 55, true),
   (3, 56, true),
   (3, 57, true),
   (3, 59, true),
   (3, 60, true),
   (3, 61, true),
   (3, 62, true),
   (3, 12, true),
   (3, 13, true),
   (3, 9, false),
   (3, 10, false),
   (3, 11, false),
   (3, 24, false),
   (3, 25, false),
   (3, 37, false),
   (3, 38, false),
   (4, 63, true),
   (4, 64, true),
   (4, 65, true),
   (4, 66, true),
   (4, 67, true),
   (4, 69, true),
   (4, 71, true),
   (4, 72, true),
   (4, 46, false),
   (4, 10, false),
   (4, 11, false),
   (4, 12, false);

INSERT INTO listen (user_id, song_id, count)
  VALUES
  (2, 1, 1),
  (3, 1, 6),
  (4, 1, 1),
  (2, 2, 7),
  (4, 2, 5),
  (1, 3, 9),
  (1, 4, 26),
  (2, 4, 28),
  (4, 4, 11),
  (1, 5, 20),
  (1, 6, 30),
  (2, 7, 10),
  (3, 7, 13),
  (4, 7, 3),
  (3, 8, 1);

QUERY
