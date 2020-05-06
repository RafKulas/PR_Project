typedef struct player_t player_t;
typedef struct point_t point_t;
typedef enum move_t move_t;

//just point
struct point_t
{
    int x,y;
};

struct player_t
{
    point_t cords;
    point_t vel;

};

//DEPEND ON CLIENT PREFERENCES
enum move_t
{
    UP,
    LEFT,
    RIGHT,
    END,
};

void init_player(player_t* player);

void remove_player(player_t* player);

void make_move(player_t* player, move_t move);