#include <stdio.h>
#include <gtk/gtk.h>
#include "utils.h"
// #include "gui.h"

enum tileStates
{
    None,
    X,
    O
};

static int gameBoard[3][3] = {{None, None, None},
                              {None, None, None},
                              {None, None, None}};

static GtkButton *buttons[3][3];
static GtkLabel *status;
static int PlayerTurn = X;

char numToChar(int num)
{
    switch (num)
    {
    case 0:
        return ' ';
        break;
    case 1:
        return 'X';
        break;
    case 2:
        return 'O';
        break;
    default:
        return 'Z';
        break;
    }
    return 'Z';
}

void print2DArray(int size, int (*array)[size][size])
{
    int x, y;
    for (x = 0; x < size; x++)
    {
        for (y = 0; y < size; y++)
        {
            printf("%c", numToChar((*array)[y][x]));
        }
        printf("\n");
    }
}

void relableGrid()
{
    int x, y;
    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            gtk_button_set_label(buttons[y][x], g_strdup_printf("%c", numToChar(gameBoard[y][x])));
        }
    }
}

int checkGridForWin(){
    int i;
    for(i = 0; i < 3; i++){
        if(gameBoard[i][0] == PlayerTurn && gameBoard[i][1] == PlayerTurn && gameBoard[i][2] == PlayerTurn){
            return PlayerTurn;
        }
        if(gameBoard[0][i] == PlayerTurn && gameBoard[1][i] == PlayerTurn && gameBoard[2][i] == PlayerTurn){
            return PlayerTurn;
        }
    }
    if(gameBoard[0][0] == PlayerTurn && gameBoard[1][1] == PlayerTurn && gameBoard[2][2] == PlayerTurn){
            return PlayerTurn;
    }
    if(gameBoard[2][0] == PlayerTurn && gameBoard[1][1] == PlayerTurn && gameBoard[0][2] == PlayerTurn){
            return PlayerTurn;
    }
    return None;
    
}

void updateStatus(int isWinner, int player) {
    char txtBuf[8];
    if(isWinner == 1){
        snprintf(txtBuf, 8, "%c Wins", numToChar(player));
    }else{
        snprintf(txtBuf, 8, "%c Turn", numToChar(player));
    }
    gtk_label_set_label(status, txtBuf);
}

static void tileIsClicked(struct intVector2 *vec)
{
    printf("%d", vec->x);
    printf(", ");
    printf("%d", vec->y);
    printf("\n");

    if(PlayerTurn == None){
        return;
    }

    gameBoard[vec->y][vec->x] = PlayerTurn;
    relableGrid();

    switch(checkGridForWin()){
        case None:
            break;
        case X:
            printf("X Wins");
            printf("\n");
            updateStatus(1, X);
            PlayerTurn = None;
            break;
        case O:
            printf("O Wins");
            printf("\n");
            updateStatus(1, O);
            PlayerTurn = None;
            break;
    }
    if(PlayerTurn == None){
        return;
    }
    if (PlayerTurn == X)
    {
        PlayerTurn = O;
    }
    else if (PlayerTurn == O)
    {
        PlayerTurn = X;
    }
    updateStatus(0, PlayerTurn);



}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *label;

    /* create a new window, and set its title */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    /* Here we construct the container that is going pack our buttons */
    grid = gtk_grid_new();

    /* Pack the container in the window */
    gtk_container_add(GTK_CONTAINER(window), grid);

    label = gtk_label_new("TicTakDoh");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 3, 1);
    status = GTK_LABEL(label);

    int x, y;
    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            button = gtk_button_new_with_label(g_strdup_printf("%c", numToChar(gameBoard[y][x])));
            buttons[y][x] = GTK_BUTTON(button);
            gtk_grid_attach(GTK_GRID(grid), button, x, y + 1, 1, 1);
            struct intVector2 *vec = malloc(sizeof(intVector2));
            vec->x = x;
            vec->y = y;
            g_signal_connect_swapped(button, "clicked", G_CALLBACK(tileIsClicked), vec);
        }
    }
    button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_grid_attach(GTK_GRID(grid), button, 0, 5, 2, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    print2DArray(3, &gameBoard);

    app = gtk_application_new("me.henzo.ticTakDoh", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    print2DArray(3, &gameBoard);

    return status;
}
