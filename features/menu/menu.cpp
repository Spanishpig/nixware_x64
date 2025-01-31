// features/menu/menu.cpp
#include "menu.h"
#include "../lua/lua.h"

c_menu g_menu;

void c_menu::init() {
    if (m_init) return;

    // Crée une fenêtre principale
    c_window* main_window = new c_window(_w("MAIN WINDOW"), bounds(100, 100, 860, 600), true);

    // Ajoute des onglets (exemple : Rage, Visuals, etc.)
    c_tab* tab_first = main_window->add_tab(_w("Rage"));
    {
        c_subtab* subtab_one = tab_first->add_subtab(_w("Aimbot"));
        {
            subtab_one->add_checkbox(_w("Enable"), _w("aim"));
            subtab_one->add_slider(_w("FOV"), _w("aim_fov"), 0.f, 180.f, _w("%.1f"));
        }
        tab_first->pushback_subtab(subtab_one);
    }
    main_window->pushback_tab(tab_first);

    // Ajoute la fenêtre à la liste
    this->m_windows.push_back(main_window);
    m_init = true;
}

void c_menu::render() {
    if (!m_opened) return;

    // Dessine chaque fenêtre
    for (auto window : m_windows)
        window->render();

    // Dessine le curseur personnalisé
    draw_cursor();
}

void c_menu::update_input() {
    // Gère les entrées clavier et souris
    std::copy(m_keystate, m_keystate + 255, m_oldstate);

    for (auto n = 0; n < 255; ++n)
        m_keystate[n] = GetAsyncKeyState(n);

    POINT p;
    if (!GetCursorPos(&p))
        return;

    ScreenToClient(init::window, &p);

    if (GetAsyncKeyState(VK_LBUTTON) && g_mouse.needs_reset)
        return;
    else if (g_mouse.needs_reset)
        g_mouse.needs_reset = false;

    g_mouse.pos = p;

    if (GetAsyncKeyState(VK_LBUTTON) && !g_mouse.is_pressed && !g_mouse.is_holding) {
        g_mouse.is_pressed = true;
        g_mouse.press_pos = p;
    }
    else if (GetAsyncKeyState(VK_LBUTTON) && !g_mouse.is_holding) {
        g_mouse.is_pressed = false;
        g_mouse.is_holding = true;
        g_mouse.hold_pos = p;
    }
    else if (!GetAsyncKeyState(VK_LBUTTON)) {
        g_mouse.is_pressed = false;
        g_mouse.is_holding = false;
    }
    else if (g_mouse.is_holding) {
        g_mouse.hold_pos = p;
    }
}

void c_menu::draw_cursor() {
    // Dessine un curseur personnalisé
    D3DCOLOR main_color = D3DCOLOR_RGBA(20, 179, 178, 255);
    D3DCOLOR back_color = D3DCOLOR_RGBA(189, 201, 221, 255);

    POINT p1; p1.x = g_mouse.pos.x; p1.y = g_mouse.pos.y;
    POINT p2; p2.x = g_mouse.pos.x + 24; p2.y = g_mouse.pos.y + 12;
    POINT p3; p3.x = g_mouse.pos.x + 12; p3.y = g_mouse.pos.y + 24;
    render::get().filled_triangle(p1, p2, p3, main_color);

    POINT p4; p4.x = g_mouse.pos.x + 3; p4.y = g_mouse.pos.y + 3;
    POINT p5; p5.x = g_mouse.pos.x + 23; p5.y = g_mouse.pos.y + 13;
    POINT p6; p6.x = g_mouse.pos.x + 13; p6.y = g_mouse.pos.y + 23;
    render::get().filled_triangle(p4, p5, p6, back_color);
}

bool& c_menu::get_opened() {
    return m_opened;
}

void c_menu::toggle() {
    m_opened = !m_opened;
}
