var_name = "Gean"
var_age = 23

config = {
  title = "T01 - Lua Test",
  fullscreen = true,
  resolution ={
    width = 800,
    height = 600
  },
}

function factorial(n)
  if n == 0 then
    return 1
  else
    return n * factorial(n - 1)
  end
end

var_pow = pow(2,4)

print("[LUA] script01.lua loaded")
print("[LUA] var_name = " .. var_name)
print("[LUA] var_age = " .. var_age)
print("[LUA] var_pow = " .. var_pow)