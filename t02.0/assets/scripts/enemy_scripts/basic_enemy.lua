function on_collision(other)
  this_tag = get_tag(this)
  other_tag = get_tag(other)

  print("Collision between " .. this_tag .. " and " .. other_tag)
end
