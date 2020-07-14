#include "ECS/Systems.h"

Collision::Collision(MapManager &map_manager, Entity &player) :
	map_manager(&map_manager),
	player(&player),
	player_pos(player.Get<Position>()) {}

void Collision::Update()
{
	auto entity = map_manager->entities[map_manager->GetChunkCoords()].begin();
	auto end = map_manager->entities[map_manager->GetChunkCoords()].end();
	while (entity != end)
	{
		Position *obj = (*entity)->Get<Position>();
		if (player_pos->pos_x == obj->pos_x && player_pos->pos_y == obj->pos_y)
		{
			if ((*entity)->Get<Type>()->type == TYPE_COIN)
			{
				player->Get<GameStats>()->coins++;
				map_manager->Destroy(entity);
				break;
			}
		}
		
		++entity;
	}
}