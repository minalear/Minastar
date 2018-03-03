//
// Created by Trevor Fisher on 2/13/2018.
//

#include "sinistar.h"
#include "../world.h"
#include "../campaign.h"

const int SINISTAR_HEALTH = 200;

void generate_sinistar_shape(sinistar *sinistar) {
    int vertex_count = 68;
    float *buffer_data = new float[vertex_count * 5];

    //Initialize all data to 1.f
    for (int i = 0; i < vertex_count; i++) {
        buffer_data[i * 5 + 0] = 0.f;
        buffer_data[i * 5 + 1] = 0.f;
        buffer_data[i * 5 + 2] = 0.65f;
        buffer_data[i * 5 + 3] = 0.15f;
        buffer_data[i * 5 + 4] = 0.15f;
    }

    const float sinistar_scale = 8.f;

    //region /* Sinistar Point Data */
    buffer_data[0] = -7.00f * sinistar_scale;
    buffer_data[1] = -7.50f * sinistar_scale;

    buffer_data[5] = -4.00f * sinistar_scale;
    buffer_data[6] = -3.50f * sinistar_scale;

    buffer_data[10] = -5.00f * sinistar_scale;
    buffer_data[11] = -1.50f * sinistar_scale;

    buffer_data[15] = -4.00f * sinistar_scale;
    buffer_data[16] = 0.50f * sinistar_scale;

    buffer_data[20] = -5.00f * sinistar_scale;
    buffer_data[21] = 3.50f * sinistar_scale;

    buffer_data[25] = -2.00f * sinistar_scale;
    buffer_data[26] = 6.50f * sinistar_scale;

    buffer_data[30] = 2.00f * sinistar_scale;
    buffer_data[31] = 6.50f * sinistar_scale;

    buffer_data[35] = 5.00f * sinistar_scale;
    buffer_data[36] = 3.50f * sinistar_scale;

    buffer_data[40] = 4.00f * sinistar_scale;
    buffer_data[41] = 0.50f * sinistar_scale;

    buffer_data[45] = 5.00f * sinistar_scale;
    buffer_data[46] = -1.50f * sinistar_scale;

    buffer_data[50] = 4.00f * sinistar_scale;
    buffer_data[51] = -3.50f * sinistar_scale;

    buffer_data[55] = 3.00f * sinistar_scale;
    buffer_data[56] = -6.50f * sinistar_scale;

    buffer_data[60] = 7.00f * sinistar_scale;
    buffer_data[61] = -7.50f * sinistar_scale;

    buffer_data[65] = 4.00f * sinistar_scale;
    buffer_data[66] = -3.50f * sinistar_scale;

    buffer_data[70] = 1.00f * sinistar_scale;
    buffer_data[71] = -2.00f * sinistar_scale;

    buffer_data[75] = 3.00f * sinistar_scale;
    buffer_data[76] = -1.50f * sinistar_scale;

    buffer_data[80] = 3.50f * sinistar_scale;
    buffer_data[81] = -3.25f * sinistar_scale;

    buffer_data[85] = 0.00f * sinistar_scale;
    buffer_data[86] = -1.50f * sinistar_scale;

    buffer_data[90] = -3.50f * sinistar_scale;
    buffer_data[91] = -3.25f * sinistar_scale;

    buffer_data[95] = -3.00f * sinistar_scale;
    buffer_data[96] = -1.50f * sinistar_scale;

    buffer_data[100] = -1.00f * sinistar_scale;
    buffer_data[101] = -2.00f * sinistar_scale;

    buffer_data[105] = -4.00f * sinistar_scale;
    buffer_data[106] = -3.50f * sinistar_scale;

    buffer_data[110] = -3.25f * sinistar_scale;
    buffer_data[111] = -5.75f * sinistar_scale;

    buffer_data[115] = 0.00f * sinistar_scale;
    buffer_data[116] = -2.50f * sinistar_scale;

    buffer_data[120] = 3.25f * sinistar_scale;
    buffer_data[121] = -5.75f * sinistar_scale;

    buffer_data[125] = 3.00f * sinistar_scale;
    buffer_data[126] = -6.50f * sinistar_scale;

    buffer_data[130] = 0.00f * sinistar_scale;
    buffer_data[131] = -5.50f * sinistar_scale;

    buffer_data[135] = -3.00f * sinistar_scale;
    buffer_data[136] = -6.50f * sinistar_scale;

    buffer_data[140] = -3.25f * sinistar_scale;
    buffer_data[141] = -5.75f * sinistar_scale;

    buffer_data[145] = -4.00f * sinistar_scale;
    buffer_data[146] = -3.50f * sinistar_scale;

    buffer_data[150] = -6.06f * sinistar_scale;
    buffer_data[151] = -6.25f * sinistar_scale;

    buffer_data[155] = -8.00f * sinistar_scale;
    buffer_data[156] = 1.50f * sinistar_scale;

    buffer_data[160] = -3.00f * sinistar_scale;
    buffer_data[161] = 7.50f * sinistar_scale;

    buffer_data[165] = 3.00f * sinistar_scale;
    buffer_data[166] = 7.50f * sinistar_scale;

    buffer_data[170] = 8.00f * sinistar_scale;
    buffer_data[171] = 1.50f * sinistar_scale;

    buffer_data[175] = 6.06f * sinistar_scale;
    buffer_data[176] = -6.25f * sinistar_scale;

    buffer_data[180] = 7.00f * sinistar_scale;
    buffer_data[181] = -7.50f * sinistar_scale;

    buffer_data[185] = 5.00f * sinistar_scale;
    buffer_data[186] = -7.00f * sinistar_scale;

    buffer_data[190] = 0.00f * sinistar_scale;
    buffer_data[191] = -8.50f * sinistar_scale;

    buffer_data[195] = -5.00f * sinistar_scale;
    buffer_data[196] = -7.00f * sinistar_scale;

    buffer_data[200] = -7.00f * sinistar_scale;
    buffer_data[201] = -7.50f * sinistar_scale;

    buffer_data[205] = -3.00f * sinistar_scale;
    buffer_data[206] = -6.50f * sinistar_scale;

    buffer_data[210] = -4.00f * sinistar_scale;
    buffer_data[211] = -3.50f * sinistar_scale;

    buffer_data[215] = 0.00f * sinistar_scale;
    buffer_data[216] = -1.50f * sinistar_scale;

    buffer_data[220] = 0.00f * sinistar_scale;
    buffer_data[221] = -1.00f * sinistar_scale;

    buffer_data[225] = -0.50f * sinistar_scale;
    buffer_data[226] = 0.50f * sinistar_scale;

    buffer_data[230] = 0.50f * sinistar_scale;
    buffer_data[231] = 0.50f * sinistar_scale;

    buffer_data[235] = 0.00f * sinistar_scale;
    buffer_data[236] = -1.00f * sinistar_scale;

    buffer_data[240] = 0.00f * sinistar_scale;
    buffer_data[241] = 1.50f * sinistar_scale;

    buffer_data[245] = -1.00f * sinistar_scale;
    buffer_data[246] = 1.50f * sinistar_scale;

    buffer_data[250] = -1.50f * sinistar_scale;
    buffer_data[251] = 2.50f * sinistar_scale;

    buffer_data[255] = -2.00f * sinistar_scale;
    buffer_data[256] = 1.50f * sinistar_scale;

    buffer_data[260] = -3.00f * sinistar_scale;
    buffer_data[261] = 0.50f * sinistar_scale;

    buffer_data[265] = -3.00f * sinistar_scale;
    buffer_data[266] = 2.50f * sinistar_scale;

    buffer_data[270] = -1.50f * sinistar_scale;
    buffer_data[271] = 3.50f * sinistar_scale;

    buffer_data[275] = -1.00f * sinistar_scale;
    buffer_data[276] = 2.50f * sinistar_scale;

    buffer_data[280] = -0.50f * sinistar_scale;
    buffer_data[281] = 3.50f * sinistar_scale;

    buffer_data[285] = 0.50f * sinistar_scale;
    buffer_data[286] = 3.50f * sinistar_scale;

    buffer_data[290] = 1.00f * sinistar_scale;
    buffer_data[291] = 2.50f * sinistar_scale;

    buffer_data[295] = 1.50f * sinistar_scale;
    buffer_data[296] = 3.50f * sinistar_scale;

    buffer_data[300] = 3.00f * sinistar_scale;
    buffer_data[301] = 2.50f * sinistar_scale;

    buffer_data[305] = 3.00f * sinistar_scale;
    buffer_data[306] = 0.50f * sinistar_scale;

    buffer_data[310] = 2.00f * sinistar_scale;
    buffer_data[311] = 1.50f * sinistar_scale;

    buffer_data[315] = 1.50f * sinistar_scale;
    buffer_data[316] = 2.50f * sinistar_scale;

    buffer_data[320] = 1.00f * sinistar_scale;
    buffer_data[321] = 1.50f * sinistar_scale;

    buffer_data[325] = 0.00f * sinistar_scale;
    buffer_data[326] = 1.50f * sinistar_scale;

    buffer_data[330] = 0.00f * sinistar_scale;
    buffer_data[331] = -1.50f * sinistar_scale;

    buffer_data[335] = -4.00f * sinistar_scale;
    buffer_data[336] = -3.50f * sinistar_scale;
    //endregion /* Sinistar Point Data */

    sinistar->vertex_count = vertex_count;
    sinistar->buffer_data = buffer_data;
    sinistar->bounding_radius = sinistar_scale * 8.1394f;
}

sinistar::sinistar(glm::vec2 pos) {
    generate_sinistar_shape(this);

    set_health(SINISTAR_HEALTH);
    this->entity_type = ENTITY_TYPES::Sinistar;
    this->position = pos;
    this->friction_coefficient = 0.9f;
    this->movement_speed = 15.f;

    this->set_collision_category(COLLISION_CATEGORIES::Enemy);
    this->add_collision_type(COLLISION_CATEGORIES::Player);
    this->add_collision_type(COLLISION_CATEGORIES::Ally_Bullet);
    this->add_collision_type(COLLISION_CATEGORIES::Asteroid);
}

void sinistar::update(float dt) {
    if (campaign.sinistar_released) {
        if (campaign.player_entity) {
            seek(campaign.player_entity->position);
        }
    }

    game_entity::update(dt);
}

void sinistar::handle_collision(game_entity &other, glm::vec2 point) {
    if (other.entity_type == ENTITY_TYPES::Asteroid || other.entity_type == ENTITY_TYPES::Player) {
        other.damage(*this, other.health);
    }
}