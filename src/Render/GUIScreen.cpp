#include "Render/GUIScreen.h"

GUIScreen::GUIScreen(const MapManager *map_manager, const Entity *player, const MenuProperties *menu_prop,
                     const Localization *localization)
    : map_manager(map_manager),
      player(player),
      menu_prop(menu_prop),
      localization(localization),
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
  RenderRecords();

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
  Print(COLOR_WHITE, 1, 1, "%s = ", localization->local.at("health").c_str());
  Print(COLOR_YELLOW, 15, 1, "%d", player_def->health);
  Print(COLOR_WHITE, 22, 1, "%s = ", localization->local.at("armor").c_str());
  Print(COLOR_YELLOW, 35, 1, "%d", player_def->armor);
}
void GUIScreen::RenderPlayerStats() const {
  Print(COLOR_BLUE, 1, pos_stats_y, "%s", localization->local.at("statistics").c_str());
  Print(COLOR_WHITE, 1, pos_stats_y + 2, "%s = ", localization->local.at("coins").c_str());
  Print(COLOR_YELLOW, 20, pos_stats_y + 2, "%d", player_stats->coins);
  Print(COLOR_WHITE, 1, pos_stats_y + 3, "%s = ", localization->local.at("step_count").c_str());
  Print(COLOR_YELLOW, 20, pos_stats_y + 3, "%d", player_stats->step_count);
}
void GUIScreen::RenderInventory() const {
  Print(COLOR_BLUE, pos_inv_x + 1, pos_inv_y + 1, "%s", localization->local.at("inventory").c_str());
  Print(COLOR_AQUA, pos_inv_x + 1, pos_inv_y + 3 + player_inv->cursor * 2, ">");
  const int items_count = player_inv->inventory.size();
  for (int i = 0; i < player_inv->max_items; ++i) {
    if (i < items_count) {
      switch (player_inv->inventory[i].get()->Get<Type>()->type) {
        case TYPE_SWORD:
          Print(COLOR_WHITE, pos_inv_x + 3, pos_inv_y + 3 + i * 2, "%s", localization->local.at("sword").c_str());
          break;
        case TYPE_BOMB:
          Print(COLOR_WHITE, pos_inv_x + 3, pos_inv_y + 3 + i * 2, "%s", localization->local.at("bomb").c_str());
          break;
        case TYPE_CHEST:
          Print(COLOR_WHITE, pos_inv_x + 3, pos_inv_y + 3 + i * 2, "%s", localization->local.at("chest").c_str());
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
  const int offset = 72;
  Print(COLOR_BLUE, offset, pos_stats_y, "%s", localization->local.at("selected_item").c_str());
  Print(COLOR_WHITE, offset, pos_stats_y + 1, "%s = ", localization->local.at("durability_count").c_str());
  Print(COLOR_WHITE, offset, pos_stats_y + 2, "%s = ", localization->local.at("health_damage").c_str());
  Print(COLOR_WHITE, offset, pos_stats_y + 3, "%s = ", localization->local.at("armor_damage").c_str());
  if (player_inv->cursor < static_cast<int>(player_inv->inventory.size()) &&
      player_inv->inventory.at(player_inv->cursor).get()->Get<Type>()->type != TYPE_CHEST) {
    const Weapon *current_weapon = player_inv->inventory.at(player_inv->cursor).get()->Get<Weapon>();
    Print(COLOR_YELLOW, offset + 25, pos_stats_y + 1, "%d", current_weapon->durability);
    Print(COLOR_YELLOW, offset + 25, pos_stats_y + 2, "%d", current_weapon->health_damage);
    Print(COLOR_YELLOW, offset + 25, pos_stats_y + 3, "%d", current_weapon->armor_damage);
  } else {
    Print(COLOR_YELLOW, offset + 25, pos_stats_y + 1, "--");
    Print(COLOR_YELLOW, offset + 25, pos_stats_y + 2, "--");
    Print(COLOR_YELLOW, offset + 25, pos_stats_y + 3, "--");
  }
}
void GUIScreen::RenderFightingInfo() const {
  const int offset = 40;
  Print(COLOR_BLUE, offset, pos_stats_y, "%s", localization->local.at("enemy_info").c_str());
  Print(COLOR_WHITE, offset, pos_stats_y + 2, "%s = ", localization->local.at("health").c_str());
  Print(COLOR_WHITE, offset, pos_stats_y + 3, "%s = ", localization->local.at("armor").c_str());
  const entity_ptr entity =
      map_manager->GetEntity(map_manager->GetChunkCoords(player_pos), map_manager->GlobalToLocal(player_pos));
  if (entity.valid && entity.iter->get()->Get<Type>()->type == TYPE_ENEMY) {
    const Defense *enemy_def = entity.iter->get()->Get<Defense>();
    Print(COLOR_YELLOW, offset + 14, pos_stats_y + 2, "%d", enemy_def->health);
    Print(COLOR_YELLOW, offset + 14, pos_stats_y + 3, "%d", enemy_def->armor);
  } else {
    Print(COLOR_YELLOW, offset + 14, pos_stats_y + 2, "--");
    Print(COLOR_YELLOW, offset + 14, pos_stats_y + 3, "--");
  }
}
void GUIScreen::RenderRecords() const {
  Print(COLOR_BLUE, 1, pos_game_y + 1, "%s", localization->local.at("records").c_str());
  const int records_count = player_stats->records.size();
  for (int i = 0; i < player_stats->max_records; ++i) {
    Print(COLOR_WHITE, 1, pos_game_y + 3 + i * 2, "%d.", i + 1);
    if (i < records_count)
      Print(COLOR_YELLOW, 4, pos_game_y + 3 + i * 2, "%d", player_stats->records.at(i));
    else
      Print(COLOR_GREY, 4, pos_game_y + 3 + i * 2, "...");
  }
}