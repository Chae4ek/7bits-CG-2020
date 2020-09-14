#include "Render/GUIScreen.h"

GUIScreen::GUIScreen(const MapManager *map_manager, const Entity *player)
    : map_manager(map_manager),
      player_stats(player->Get<GameStats>()),
      player_inv(player->Get<Inventory>()),
      player_def(player->Get<Defense>()),
      pos_inv_x(pos_game_x + map_manager->size_x + 1),
      pos_inv_y(pos_game_y),
      pos_stats_x(0),
      pos_stats_y(map_manager->size_y + pos_game_y + 1) {}

void GUIScreen::Update() const {
  // interface
  terminal_color(COLOR_BLUE);
  for (int i = 0; i < terminal_state(TK_WIDTH); ++i) {
    terminal_put(i, pos_game_y - 1, PREFABS.at(TYPE_WALL).hex_texture);
    terminal_put(i, pos_stats_y - 1, PREFABS.at(TYPE_WALL).hex_texture);
  }
  for (int i = pos_game_y; i < pos_stats_y - 1; ++i) {
    terminal_put(pos_game_x - 1, i, PREFABS.at(TYPE_WALL).hex_texture);
    terminal_put(pos_inv_x - 1, i, PREFABS.at(TYPE_WALL).hex_texture);
  }

  // defense
  Print(COLOR_WHITE, 1, 1, "Health = ");
  Print(COLOR_YELLOW, 10, 1, "%d", player_def->health);
  Print(COLOR_WHITE, 20, 1, "Armor = ");
  Print(COLOR_YELLOW, 28, 1, "%d", player_def->armor);

  // player stats
  Print(COLOR_BLUE, 1, pos_stats_y, "Statistics");
  Print(COLOR_WHITE, 1, pos_stats_y + 1, "Coins = ");
  Print(COLOR_YELLOW, 9, pos_stats_y + 1, "%d", player_stats->coins);
  Print(COLOR_WHITE, 1, pos_stats_y + 3, "Step count = ");
  Print(COLOR_YELLOW, 14, pos_stats_y + 3, "%d", player_stats->step_count);

  // inv
  Print(COLOR_BLUE, pos_inv_x + 1, pos_inv_y + 1, "Inventory");
  Print(COLOR_AQUA, pos_inv_x + 1, pos_inv_y + 3 + player_inv->cursor * 2, ">");
  const int items_count = player_inv->inventory.size();
  for (int i = 0; i < player_inv->max_items; ++i) {
    if (i < items_count) {
      switch (player_inv->inventory[i].get()->Get<Type>()->type) {
        case TYPE_SWORD:
          Print(COLOR_WHITE, pos_inv_x + 3, pos_inv_y + 3 + i * 2, "Sword");
          break;
        case TYPE_BOMB:
          Print(COLOR_WHITE, pos_inv_x + 3, pos_inv_y + 3 + i * 2, "Bomb");
          break;
        case TYPE_CHEST:
          Print(COLOR_WHITE, pos_inv_x + 3, pos_inv_y + 3 + i * 2, "Chest");
          break;
        default:
          break;
      }
    } else {
      Print(COLOR_GREY, pos_inv_x + 3, pos_inv_y + 3 + i * 2, "...");
    }
  }

  // inv stats
  const int offset = 75;
  Print(COLOR_BLUE, offset, pos_stats_y, "Selected item");
  Print(COLOR_WHITE, offset, pos_stats_y + 1, "Durability / Count = ");
  Print(COLOR_WHITE, offset, pos_stats_y + 2, "Health damage = ");
  Print(COLOR_WHITE, offset, pos_stats_y + 3, "Armor damage = ");
  if (player_inv->cursor < items_count &&
      player_inv->inventory.at(player_inv->cursor).get()->Get<Type>()->type != TYPE_CHEST) {
    const Weapon *current_weapon = player_inv->inventory.at(player_inv->cursor).get()->Get<Weapon>();
    Print(COLOR_YELLOW, offset + 21, pos_stats_y + 1, "%d", current_weapon->durability);
    Print(COLOR_YELLOW, offset + 16, pos_stats_y + 2, "%d", current_weapon->health_damage);
    Print(COLOR_YELLOW, offset + 15, pos_stats_y + 3, "%d", current_weapon->armor_damage);
  } else {
    Print(COLOR_YELLOW, offset + 21, pos_stats_y + 1, "--");
    Print(COLOR_YELLOW, offset + 16, pos_stats_y + 2, "--");
    Print(COLOR_YELLOW, offset + 15, pos_stats_y + 3, "--");
  }

  terminal_refresh();
}