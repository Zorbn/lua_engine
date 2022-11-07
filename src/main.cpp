#include <stdexcept>
#include <iostream>
#include <lua.hpp>
#include <sol/sol.hpp>

#include "graphics.hpp"

bool check_lua(lua_State* lua_state, int ret) {
    if (ret != LUA_OK) {
        std::string error_msg = lua_tostring(lua_state, -1);
        std::cout << error_msg << "\n";
        return false;
    }

    return true;
}

int dont_return_the_number_five(int num_a, int num_b) {
    int sum = num_a + num_b;
    if (sum == 5) sum++;
    return sum;
}

void error_callback(int code, const char* description) {
    std::cout << code << description << std::endl;
}

int main(void) {
    sol::state lua;
    lua.open_libraries();
    lua.script("print('hi')");
    lua.new_usertype<texture_array>(
        "texture_array",
        sol::constructors<texture_array(std::vector<std::string>)>());
    lua.new_usertype<shader>(
        "shader",
        sol::constructors<shader(), shader(const std::string& vertex_code, const std::string& fragment_code)>(),
        "from_file",
        &shader::from_file);
    lua.new_usertype<graphics>(
        "graphics",
        sol::constructors<graphics(const std::string&, int32_t, int32_t)>(),
        "draw_sprite",
        &graphics::draw_sprite,
        "is_key_held",
        &graphics::is_key_held,
        "was_key_pressed",
        &graphics::was_key_pressed,
        "was_key_released",
        &graphics::was_key_released);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Lua Engine", nullptr, nullptr);
    // graphics g("Lua Engine", 640, 480);

    camera cam;
    cam.z = 1.0f;
    cam.setBackgroundColor(100, 149, 237);

    // shader sprite_shader;

    // texture_array tex_array({
    //     "test_img_0.png",
    //     "test_img_1.png",
    //     "test_img_2.png",
    // });

    // lua.set("test.g", &g);
    // lua.set("test.tex_array", &tex_array);
    // lua.set("test.sprite_shader", &sprite_shader);
    sol::table key_table = lua["key"].get_or_create<sol::table>();
    key_table["unknown"] = -1;
    key_table["space"] = 32;
    key_table["apostrophe"] = 39;
    key_table["comma"] = 44;
    key_table["minus"] = 45;
    key_table["period"] = 46;
    key_table["slash"] = 47;
    key_table["0"] = 48;
    key_table["1"] = 49;
    key_table["2"] = 50;
    key_table["3"] = 51;
    key_table["4"] = 52;
    key_table["5"] = 53;
    key_table["6"] = 54;
    key_table["7"] = 55;
    key_table["8"] = 56;
    key_table["9"] = 57;
    key_table["semicolon"] = 59;
    key_table["equal"] = 61;
    key_table["a"] = 65;
    key_table["b"] = 66;
    key_table["c"] = 67;
    key_table["d"] = 68;
    key_table["e"] = 69;
    key_table["f"] = 70;
    key_table["g"] = 71;
    key_table["h"] = 72;
    key_table["i"] = 73;
    key_table["j"] = 74;
    key_table["k"] = 75;
    key_table["l"] = 76;
    key_table["m"] = 77;
    key_table["n"] = 78;
    key_table["o"] = 79;
    key_table["p"] = 80;
    key_table["q"] = 81;
    key_table["r"] = 82;
    key_table["s"] = 83;
    key_table["t"] = 84;
    key_table["u"] = 85;
    key_table["v"] = 86;
    key_table["w"] = 87;
    key_table["x"] = 88;
    key_table["y"] = 89;
    key_table["z"] = 90;
    key_table["left_bracket"] = 91;
    key_table["backslash"] = 92;
    key_table["right_bracket"] = 93;
    key_table["grave_accent"] = 96;
    key_table["world_1"] = 161;
    key_table["world_2"] = 162;
    key_table["escape"] = 256;
    key_table["enter"] = 257;
    key_table["tab"] = 258;
    key_table["backspace"] = 259;
    key_table["insert"] = 260;
    key_table["delete"] = 261;
    key_table["right"] = 262;
    key_table["left"] = 263;
    key_table["down"] = 264;
    key_table["up"] = 265;
    key_table["page_up"] = 266;
    key_table["page_down"] = 267;
    key_table["home"] = 268;
    key_table["end"] = 269;
    key_table["caps_lock"] = 280;
    key_table["scroll_lock"] = 281;
    key_table["num_lock"] = 282;
    key_table["print_screen"] = 283;
    key_table["pause"] = 284;
    key_table["f1"] = 290;
    key_table["f2"] = 291;
    key_table["f3"] = 292;
    key_table["f4"] = 293;
    key_table["f5"] = 294;
    key_table["f6"] = 295;
    key_table["f7"] = 296;
    key_table["f8"] = 297;
    key_table["f9"] = 298;
    key_table["f10"] = 299;
    key_table["f11"] = 300;
    key_table["f12"] = 301;
    key_table["f13"] = 302;
    key_table["f14"] = 303;
    key_table["f15"] = 304;
    key_table["f16"] = 305;
    key_table["f17"] = 306;
    key_table["f18"] = 307;
    key_table["f19"] = 308;
    key_table["f20"] = 309;
    key_table["f21"] = 310;
    key_table["f22"] = 311;
    key_table["f23"] = 312;
    key_table["f24"] = 313;
    key_table["f25"] = 314;
    key_table["kp_0"] = 320;
    key_table["kp_1"] = 321;
    key_table["kp_2"] = 322;
    key_table["kp_3"] = 323;
    key_table["kp_4"] = 324;
    key_table["kp_5"] = 325;
    key_table["kp_6"] = 326;
    key_table["kp_7"] = 327;
    key_table["kp_8"] = 328;
    key_table["kp_9"] = 329;
    key_table["kp_decimal"] = 330;
    key_table["kp_divide"] = 331;
    key_table["kp_multiply"] = 332;
    key_table["kp_subtract"] = 333;
    key_table["kp_add"] = 334;
    key_table["kp_enter"] = 335;
    key_table["kp_equal"] = 336;
    key_table["left_shift"] = 340;
    key_table["left_control"] = 341;
    key_table["left_alt"] = 342;
    key_table["left_super"] = 343;
    key_table["right_shift"] = 344;
    key_table["right_control"] = 345;
    key_table["right_alt"] = 346;
    key_table["right_super"] = 347;
    key_table["menu"] = 348;
    key_table["last"] = key_table["menu"];

    lua.script("require('script')");

    graphics& g = lua["g"];
    texture_array& tex_array = lua["tex_array"];
    shader& sprite_shader = lua["sprite_shader"];

    sol::function lua_draw = lua["draw"];

    while (g.window_is_running()) {
        g.begin_drawing(cam, sprite_shader);
        lua_draw();
        g.end_drawing();
    }

    g.close_window();

    return 0;
}
