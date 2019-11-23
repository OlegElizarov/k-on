#include <gtest/gtest.h>

#include "db_worker_recommendations.h"


TEST(DbWorkerRecommendations, add_users) {
    DbWorkerRecommendations worker("test");

    std::vector<User> expected_users = {
            User(1, "alice", "alice"),
            User(2, "andrew", "andrew"),
            User(3, "oleg", "oleg"),
            User(4, "antony", "antony")
    };

    for (const auto &user : expected_users) {
        EXPECT_TRUE(worker.add_user(user.login, user.password));
    }

    std::vector<User> got_users = worker.get_users();
    EXPECT_EQ(expected_users, got_users);
}

TEST(DbWorkerRecommendations, add_songs) {
    DbWorkerRecommendations worker("test");

    std::vector<Song> expected_songs = {
            Song(1, "Nice Boi", "Eskimo Callboy", "metalcore", 159, "01.11.2019"),
            Song(2, "Black Files", "Ben Howard", "indie folk", 381, "30.09.2011"),
            Song(3, "Waiting for You", "Nick Cave & The Bad Seeds", "alternative rock", 234, "04.10.2019"),
            Song(4, "Hunger", "The Score", "alternative rock", 123, "09.08.2019"),
            Song(5, "Sweet Disposition", "The Temper Trap", "indie rock", 234, "01.01.2008"),
            Song(6, "Into My Arms", "Nick Cave & The Bad Seeds", "alternative rock", 256, "02.03.1997"),
            Song(7, "Prey", "The Neighbourhood", "indie pop", 282, "30.10.2015"),
            Song(8, "Mr. Brightside", "The Killers", "alternative rock", 222, "29.09.2003")
    };

    for (const auto &song : expected_songs) {
        EXPECT_TRUE(worker.add_song(song.name, song.author, song.genre, song.duration));
    }

    std::vector<Song> got_songs = worker.get_songs();
    EXPECT_EQ(expected_songs, got_songs);
}

TEST(DbWorkerRecommendations, get_new_songs) {
    DbWorkerRecommendations worker("test");
    const int size = 3;

    std::vector<Song> got_songs = worker.get_new_songs(size);
    EXPECT_EQ(size, got_songs.size());

    std::vector<int> expected_songs = {1, 3, 4};
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(expected_songs[i], got_songs[i].id);
    }
}

TEST(DbWorkerRecommendations, get_all_new_songs) {
    DbWorkerRecommendations worker("test");
    const int size = 8;

    std::vector<Song> got_songs = worker.get_new_songs(size);
    EXPECT_EQ(size, got_songs.size());

    std::vector<int> expected_songs = {1, 3, 4, 7, 2, 5, 8, 6};
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(expected_songs[i], got_songs[i].id);
    }
}

TEST(DbWorkerRecommendations, get_more_new_songs) {
    DbWorkerRecommendations worker("test");

    std::vector<Song> got_songs = worker.get_new_songs(10);
    EXPECT_EQ(8, got_songs.size());
}

TEST(DbWorkerRecommendations, add_likes_dislikes) {
    DbWorkerRecommendations worker("test");
    
    std::vector<LikeDislike> expected_likes_dislikes = {
            LikeDislike(1, 2, 1, false),
            LikeDislike(2, 3, 1, true),
            LikeDislike(3, 4, 1, false),
            LikeDislike(4, 2, 2, true),
            LikeDislike(5, 4, 2, true),
            LikeDislike(6, 1, 3, true),
            LikeDislike(7, 1, 4, true),
            LikeDislike(8, 2, 4, true),
            LikeDislike(9, 4, 4, true),
            LikeDislike(10, 1, 5, true),
            LikeDislike(11, 1, 6, true),
            LikeDislike(12, 2, 7, true),
            LikeDislike(13, 3, 7, true),
            LikeDislike(14, 4, 7, true),
            LikeDislike(15, 3, 8, false)
    };

    for (const auto &like_dislike : expected_likes_dislikes) {
        EXPECT_TRUE(worker.add_like_dislike(like_dislike.user_id, like_dislike.song_id, like_dislike.value));
    }

    std::vector<LikeDislike> got_likes_dislikes = worker.get_likes_dislikes();
    EXPECT_EQ(expected_likes_dislikes, got_likes_dislikes);
}

TEST(DbWorkerRecommendations, get_user_likes_dislikes) {
    DbWorkerRecommendations worker("test");
    const int user_id = 2;
    const int size = 4;

    std::vector<LikeDislike> got_likes_dislikes = worker.get_likes_dislikes(user_id);
    EXPECT_EQ(size, got_likes_dislikes.size());

    std::vector<LikeDislike> expected_likes_dislikes = {
            LikeDislike(1, 2, 1, false),
            LikeDislike(4, 2, 2, true),
            LikeDislike(8, 2, 4, true),
            LikeDislike(12, 2, 7, true)            
    };
    EXPECT_EQ(expected_likes_dislikes, got_likes_dislikes);
}

TEST(DbWorkerRecommendations, add_listens) {
    DbWorkerRecommendations worker("test");
    
    std::vector<Listen> expected_listens = {
            Listen(1, 2, 1, 1),
            Listen(2, 3, 1, 6),
            Listen(3, 4, 1, 1),
            Listen(4, 2, 2, 7),
            Listen(5, 4, 2, 5),
            Listen(6, 1, 3, 9),
            Listen(7, 1, 4, 26),
            Listen(8, 2, 4, 28),
            Listen(9, 4, 4, 11),
            Listen(10, 1, 5, 20),
            Listen(11, 1, 6, 30),
            Listen(12, 2, 7, 10),
            Listen(13, 3, 7, 13),
            Listen(14, 4, 7, 3),
            Listen(15, 3, 8, 1)
    };
    
    for (const auto &listen : expected_listens) {
        EXPECT_TRUE(worker.add_listen(listen.user_id, listen.song_id, listen.count));
    }

    std::vector<Listen> got_listens = worker.get_listens();
    EXPECT_EQ(expected_listens, got_listens);
}

TEST(DbWorkerRecommendations, get_user_listens) {
    DbWorkerRecommendations worker("test");
    const int user_id = 2;
    const int size = 4;

    std::vector<Listen> got_listens = worker.get_listens(user_id);
    EXPECT_EQ(size, got_listens.size());

    std::vector<Listen> expected_listens = {
            Listen(1, 2, 1, 1),
            Listen(4, 2, 2, 7),
            Listen(8, 2, 4, 28),
            Listen(12, 2, 7, 10)
    };
    EXPECT_EQ(expected_listens, got_listens);
}

TEST(DbWorkerRecommendations, get_popular_songs) {
    DbWorkerRecommendations worker("test");
    const int size = 3;

    std::vector<Song> got_songs = worker.get_popular_songs(size);
    EXPECT_EQ(size, got_songs.size());

    std::vector<int> expected_songs = {4, 7, 2};
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(expected_songs[i], got_songs[i].id);
    }
}

TEST(DbWorkerRecommendations, get_all_popular_songs) {
    DbWorkerRecommendations worker("test");
    const int size = 8;

    std::vector<Song> got_songs = worker.get_popular_songs(size);
    EXPECT_EQ(size, got_songs.size());

    std::vector<int> expected_songs = {4, 7, 2, 6, 5, 3, 1, 8};
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(expected_songs[i], got_songs[i].id);
    }
}

TEST(DbWorkerRecommendations, get_more_popular_songs) {
    DbWorkerRecommendations worker("test");

    std::vector<Song> got_songs = worker.get_popular_songs(10);
    EXPECT_EQ(8, got_songs.size());
}

TEST(DbWorkerRecommendations, set_recommendations) {
    DbWorkerRecommendations worker("test");
    const int user_id = 3;
    const int size = 3;

    std::vector<int> expected_recommendations = {3, 4, 5};
    worker.set_recommendations(user_id, expected_recommendations);

    std::vector<int> got_recommendations = worker.get_recommendations(user_id, size);
    EXPECT_EQ(expected_recommendations, got_recommendations);
}

TEST(DbWorkerRecommendations, set_new_recommendations) {
    DbWorkerRecommendations worker("test");
    const int user_id = 3;
    const int size = 3;

    std::vector<int> expected_recommendations = {2, 3, 8};
    worker.set_recommendations(user_id, expected_recommendations);

    std::vector<int> got_recommendations = worker.get_recommendations(user_id, size);
    EXPECT_EQ(expected_recommendations, got_recommendations);
}

TEST(DbWorkerRecommendations, get_recommendations) {
    DbWorkerRecommendations worker("test");
    const int user_id = 3;
    const int size = 2;

    std::vector<int> got_recommendations = worker.get_recommendations(user_id, size);
    EXPECT_EQ(size, got_recommendations.size());
}

TEST(DbWorkerRecommendations, get_more_recommendations) {
    DbWorkerRecommendations worker("test");
    const int user_id = 3;

    std::vector<int> got_recommendations = worker.get_recommendations(user_id, 5);
    EXPECT_EQ(3, got_recommendations.size());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
