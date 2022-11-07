require('other_script')

a = 7 + 5;
print('a = ' .. a)
print('sin(a) = ' .. math.sin(a))

function add(a, b)
    print('adding numbers: ', a, b)
    return a + b;
end

-- Maybe graphics should be called 'window' if it handles input?
g = graphics.new("Lua Game", 640, 480)
tex_array = texture_array.new({
    "test_img_0.png",
    "test_img_1.png",
    "test_img_2.png",
})
sprite_shader = shader.from_file("default_sprite.vert", "default_sprite.frag")

function draw()
    g:draw_sprite(tex_array, 'test_img_2.png', sprite_shader)

    if g:is_key_held(key.equal) then
        print("equal")
    end

    if g:was_key_pressed(key.b) then
        print("B")
    end

    if g:was_key_released(key.b) then
        print("no more B")
    end
end