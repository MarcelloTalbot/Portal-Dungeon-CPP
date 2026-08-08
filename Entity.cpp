#include "Entity.h"

Entity::Entity(Vec2 pos, SDL_Texture* tex) : pos(pos), tex(tex) {
	int w, h;
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	rect.w = hitbox.w = w * 3.f;
	rect.h = hitbox.h = h * 3.f;

	rect.x = pos.x - rect.w * 0.5f;//dont need cos are set when applying offset
	rect.y = pos.y - rect.h * 0.5f;
	hitbox.x = pos.x - hitbox.w * 0.5f;
	hitbox.y = pos.y - hitbox.h * 0.5f;

	health_bar.x = rect.x;
	health_bar.y = rect.y - 10.f;
	health_bar.w = rect.w;
	health_bar.h = 7.f; 
	health_bar_border = health_bar;
}
Entity::~Entity() {}

//void Entity::update(float dt) {
//	move(dt);
//}

void Entity::update(bool actions[ACTION_COUNT], UpdateParams& params) {}

void Entity::render(SDL_Renderer* renderer) const {
	//SDL_RenderCopyF(renderer, tex, nullptr, &rect);
	SDL_RenderCopyExF(renderer, tex, nullptr, &rect, toDegrees(angle), nullptr, SDL_FLIP_NONE);

	setRenderDrawColor(renderer, Colors::dark_red);
	SDL_RenderFillRectF(renderer, &health_bar_border);

	setRenderDrawColor(renderer, Colors::red);
	SDL_RenderFillRectF(renderer, &health_bar);
}

void Entity::applyOffset(Vec2 offset) {//maybe call inside render instead
	rect.x = (pos.x - rect.w * 0.5f) - offset.x;
	rect.y = (pos.y - rect.h * 0.5f) - offset.y;
	health_bar.x = rect.x;
	health_bar.y = rect.y - 10.f;
	health_bar_border.x = health_bar.x;
	health_bar_border.y = health_bar.y;
}

void Entity::move(double dt) {
	corrected_vel = vel * static_cast<float>(dt);//do I need as I reset vel to zero maybe? no for friction?
	
	pos += corrected_vel;
	//rect.x += corrected_vel.x;//dont need? cos their pos gets set when applying offset
	//rect.y += corrected_vel.y;
	hitbox.x += corrected_vel.x;
	hitbox.y += corrected_vel.y;

	//health_bar.x += corrected_vel.x;//maybe move these to a different method? as player and spawners won't move
	//health_bar.y += corrected_vel.y;
	//health_bar_border.x = health_bar.x;
	//health_bar_border.y = health_bar.y;
}

void Entity::rotateToPos(Vec2 other) {
	angle = pos.angleTo(other) + half_pi;//pi/2 only for png facing upwards
}

void Entity::findCurrentTile(TileMap& tile_map) {
	Vec2 tile_pos = pos / (tile_map.tile_size * 3.f);//make 3 be rect tile size somewhere to remove magic numbers and maybe make tile_pos a member

	current_tile = tile_map.getTile(static_cast<int>(std::floor(tile_pos.x)), static_cast<int>(std::floor(tile_pos.y)));
}

void Entity::applyTileEffects() {
	vel *= getTileProperties(current_tile).speed_mult;
}

void Entity::checkEntityCollisions(Entity& entity) {
	if (SDL_HasIntersectionF(&hitbox, &entity.hitbox)) {
		//Vec2 dir = entity.pos - pos;
		//vel -= dir;
	}
}

void Entity::checkTileCollisions(TileMap& tile_map) {//this should be using the corrected_vel
    float hitbox_right = hitbox.x + hitbox.w;
    float hitbox_bottom = hitbox.y + hitbox.h;

    int current_right_column = static_cast<int>(std::floor((hitbox_right) / (tile_map.tile_size * 3)));//maybe have 1 / tile_size saved and * instead?
    int current_left_column = static_cast<int>(std::floor(hitbox.x / (tile_map.tile_size * 3)));
    int current_top_row = static_cast<int>(std::floor(hitbox.y / (tile_map.tile_size * 3)));
    int current_bottom_row = static_cast<int>(std::floor((hitbox_bottom) / (tile_map.tile_size * 3)));
    //should get all current rows and cols
    std::vector<int> possible_col;
    std::vector<int> possible_row;

    if (vel.x > 0.f) { // Moving right
        for (int n = current_left_column; n <= static_cast<int>(std::floor((hitbox_right + vel.x) / (tile_map.tile_size * 3))); n++) {
            possible_col.push_back(n);
        }
        //for (int n = current_right_column; n < (static_cast<int>(hitbox_right + vel.x) / (tile_map.tile_size * 3)) + 1; n++) {
        //    possible_col.push_back(n);
        //}
    }
    else if (vel.x < 0.f) { // Moving left
        for (int n = static_cast<int>(std::floor((hitbox.x + vel.x) / (tile_map.tile_size * 3))); n <= current_right_column; n++) {
            possible_col.push_back(n);
        }
        //for (int n = static_cast<int>(hitbox_right + vel.x) / (tile_map.tile_size * 3); n < current_right_column + 1; n++) {
        //    possible_col.push_back(n);
        //}
                        // possible_col.reverse()
    }
    else { // No x movement
        for (int n = current_left_column; n <= current_right_column; n++) {
            possible_col.push_back(n);
        }
        //possible_col.push_back(current_left_column);
        //possible_col.push_back(current_right_column);
    }

    if (vel.y > 0.f) { // Moving down
        for (int n = current_top_row; n <= static_cast<int>(std::floor((hitbox_bottom + vel.y) / (tile_map.tile_size * 3))); n++) {
            possible_row.push_back(n);
        }
        //for (int n = current_bottom_row; n < (static_cast<int>(hitbox_bottom + vel.y) / (tile_map.tile_size * 3)) + 1; n++) {
        //    possible_row.push_back(n);
        //}
    }
    else if (vel.y < 0.f) { // Moving up
        for (int n = static_cast<int>(std::floor((hitbox.y + vel.y) / (tile_map.tile_size * 3))); n <= current_bottom_row; n++) {
            possible_row.push_back(n);
        }
        //for (int n = static_cast<int>(hitbox_bottom + vel.y) / (tile_map.tile_size * 3); n < current_bottom_row + 1; n++) {
        //    possible_row.push_back(n);
        //}
                // possible_row.reverse()
    }
    else { // No y movement
        for (int n = current_top_row; n <= current_bottom_row; n++) {
            possible_row.push_back(n);
        }
        //possible_row.push_back(current_top_row);
        //possible_row.push_back(current_bottom_row);
    }
    
    // Finds all tile centres
    std::vector<Vec2> possible_tiles;
    for (int c : possible_col) {
        for (int r : possible_row) {
            possible_tiles.push_back(Vec2(static_cast<float>((r * (tile_map.tile_size * 3)) + (tile_map.tile_size * 3) / 2), static_cast<float>((c * (tile_map.tile_size * 3)) + (tile_map.tile_size * 3) / 2)));
        }
    }

    //need to order the rows and columns from closest to furthest based on velocity path
    std::sort(possible_tiles.begin(), possible_tiles.end(), [this](const Vec2& a, const Vec2& b){ return a.distanceSqTo(pos) < b.distanceSqTo(pos); });// tile.pos.distance_to(self.pos));


    for (Vec2 centre : possible_tiles) {
        int tile_left = static_cast<int>(std::floor(centre.x / (tile_map.tile_size * 3)));
        int tile_right = tile_left + (tile_map.tile_size * 3);
        int tile_top = static_cast<int>(std::floor(centre.y / (tile_map.tile_size * 3)));
        
        if (getTileProperties(tile_map.getTile(tile_left, tile_top)).solid) {//collidable tiles maybe
            if (tile_left >= hitbox_right && vel.x > 0) {
                float ratio = (tile_left - hitbox_right) / vel.x;
                vel.x *= ratio;
                //vel.x = tile_left - hitbox_right;
            }
            else if (tile_right <= hitbox.x && vel.x < 0) {
                float ratio = (tile_right - hitbox.x) / vel.x;
                vel.x *= ratio;
                //vel.x = tile_right - hitbox.x;
            }
            break;
        }
    }
        
    for (Vec2 centre : possible_tiles) {
        int tile_left = static_cast<int>(std::floor(centre.x / (tile_map.tile_size * 3)));
        int tile_top = static_cast<int>(std::floor(centre.y / (tile_map.tile_size * 3)));
        int tile_bottom = tile_top + (tile_map.tile_size * 3);

        if (getTileProperties(tile_map.getTile(tile_left, tile_top)).solid) {
            if (tile_top >= hitbox_bottom && vel.y > 0) {
                float ratio = (tile_top - hitbox_bottom) / vel.y;
                vel.y *= ratio;
                //vel.y = tile_top - hitbox_bottom;
            }
            else if (tile_bottom <= hitbox.y && vel.y < 0) {
                float ratio = (tile_bottom - hitbox.y) / vel.y;
                vel.y *= ratio;
                //vel.y = tile_bottom - hitbox.y;
            }
            break;
        }
    }
}

void Entity::checkTileCollisions(TileMap& tile_map) {
    Vec2 current_tile_pos = pos / (tile_map.tile_size * 3.f);
    Vec2 next_tile_pos = pos + vel;// (pos + (vel * static_cast<float>(dt)));
    for (int i = static_cast<int>(std::floor(current_tile_pos.x)); i < static_cast<int>(std::floor(next_tile_pos.x)); i++) {
        for (int j = static_cast<int>(std::floor(current_tile_pos.y)); j < static_cast<int>(std::floor(next_tile_pos.y)); j++) {

        }
    }

    if (getTileProperties(tile_map.getTile(static_cast<int>(std::floor((pos.x + vel.x) / tile_map.tile_size)), static_cast<int>(std::floor((pos.y + vel.y) / tile_map.tile_size)))).solid) {

    }
}

void Entity::update_bars() {
	health_bar.w = (health / max_health) * health_bar_border.w;
}