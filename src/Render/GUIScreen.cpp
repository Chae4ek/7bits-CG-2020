#include "Render/GUIScreen.h"

GUIScreen::GUIScreen(const MapManager *map_manager, const Entity *player, const MenuProperties *menu_prop)
    : map_manager(map_manager),
      player(player),
      menu_prop(menu_prop),
      player_stats(player->Get<GameStats>()),
      player_inv(player->Get<Inventory>()),
      player_def(player->Get<Defense>()),
      player_pos(player->Get<Position>()),
      pos_inv_x(pos_game_x + map_manager->size_x + 1),
      pos_inv_y(pos_game_y),
      pos_stats_x(0),
      pos_stats_y(map_manager->size_y + pos_game_y + 1) {}

void GUIScreen::Update() const {
  RenderInterface();
  RenderPlayerDefense();
  RenderPlayerStats();
  RenderInventory();
  RenderItemStats();
  RenderFightingInfo();

  terminal_refresh();
}

void GUIScreen::RenderInterface() const {
  const Sprite interface(PREFABS.at(TYPE_WALL).texture, COLOR_BLUE, PREFABS.at(TYPE_WALL).hex_texture);
  for (int i = 0; i < terminal_state(TK_WIDTH); ++i) {
    Print(i, pos_game_y - 1, &interface, menu_prop->new_graphics);
    Print(i, pos_stats_y - 1, &interface, menu_prop->new_graphics);
  }
  for (int i = pos_game_y; i < pos_stats_y - 1; ++i) {
    Print(pos_game_x - 1, i, &interface, menu_prop->new_graphics);
    Print(pos_inv_x - 1, i, &interface, menu_prop->new_graphics);
  }
}
void GUIScreen::RenderPlayerDefense() const {
  Print(COLOR_WHITE, 1, 1, "Health = ");
  Print(COLOR_YELLOW, 10, 1, "%d", player_def->health);
  Print(COLOR_WHITE, 20, 1, "Armor = ");
  Print(COLOR_YELLOW, 28, 1, "%d", player_def->armor);
}
void GUIScreen::RenderPlayerStats() const {
  Print(COLOR_BLUE, 1, pos_stats_y, "Statistics");
  Print(COLOR_WHITE, 1, pos_stats_y + 2, "Coins = ");
  Print(COLOR_YELLOW, 9, pos_stats_y + 2, "%d", player_stats->coins);
  Print(COLOR_WHITE, 1, pos_stats_y + 3, "Step count = ");
  Print(COLOR_YELLOW, 14, pos_stats_y + 3, "%d", player_stats->step_count);
}
void GUIScreen::RenderInventory() const {
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
}
void GUIScreen::RenderItemStats() const {
  const int offset = 75;
  Print(COLOR_BLUE, offset, pos_stats_y, "Selected item");
  Print(COLOR_WHITE, offset, pos_stats_y + 1, "Durability / Count = ");
  Print(COLOR_WHITE, offset, pos_stats_y + 2, "Health damage = ");
  Print(COLOR_WHITE, offset, pos_stats_y + 3, "Armor damage = ");
  if (player_inv->cursor < static_cast<int>(player_inv->inventory.size()) &&
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
}
void GUIScreen::RenderFightingInfo() const {
  const int offset = 45;
  Print(COLOR_BLUE, offset, pos_stats_y, "Enemy info");
  Print(COLOR_WHITE, offset, pos_stats_y + 2, "Health = ");
  Print(COLOR_WHITE, offset, pos_stats_y + 3, "Armor = ");
  const entity_ptr entity =
      map_manager->GetEntity(map_manager->GetChunkCoords(player_pos), map_manager->GlobalToLocal(player_pos));
  if (entity.valid && entity.iter->get()->Get<Type>()->type == TYPE_ENEMY) {
    const Defense *enemy_def = entity.iter->get()->Get<Defense>();
    Print(COLOR_YELLOW, offset + 9, pos_stats_y + 2, "%d", enemy_def->health);
    Print(COLOR_YELLOW, offset + 8, pos_stats_y + 3, "%d", enemy_def->armor);
  } else {
    Print(COLOR_YELLOW, offset + 9, pos_stats_y + 2, "--");
    Print(COLOR_YELLOW, offset + 8, pos_stats_y + 3, "--");
  }
}