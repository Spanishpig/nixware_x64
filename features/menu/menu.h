// features/menu/menu.h
#pragma once
#include <vector>
#include <string>
#include "external_include.h"

// Forward declarations
class c_window;
class c_tab;
class c_subtab;

class c_menu {
public:
    c_menu();
    ~c_menu();

    void init(); // Initialise le menu
    void render(); // Dessine le menu
    void update_input(); // Gère les entrées utilisateur
    void draw_cursor(); // Dessine le curseur personnalisé

    bool& get_opened(); // Retourne l'état du menu (ouvert/fermé)
    void toggle(); // Bascule l'état du menu

private:
    std::vector<c_window*> m_windows; // Liste des fenêtres du menu
    bool m_init = false; // Indicateur d'initialisation
    bool m_opened = false; // État du menu (ouvert/fermé)

    // Gestion des entrées
    bool m_keystate[256] = { false };
    bool m_oldstate[256] = { false };

    // État de la souris
    struct {
        POINT pos;
        POINT press_pos;
        POINT hold_pos;
        bool is_pressed = false;
        bool is_holding = false;
        bool needs_reset = false;
    } g_mouse;
};
