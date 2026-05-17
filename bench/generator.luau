-- generator.luau

function generate_test(n, test_type)
    print(n)
    
    if test_type == "random" then
        math.randomseed(os.time())
        for i = 1, n do
            -- Generate a 32-bit signed integer using math.random()
            local val = math.floor(math.random() * 4294967296 - 2147483648)
            print(val)
        end
    elseif test_type == "sorted" then
        for i = 1, n do
            print(i)
        end
    elseif test_type == "reverse" then
        for i = n, 1, -1 do
            print(i)
        end
    elseif test_type == "nearly_sorted" then
        local a = {}
        for i = 1, n do
            a[i] = i
        end
        
        math.randomseed(os.time())
        local swaps = math.floor(n * 0.01)
        for _ = 1, swaps do
            local i = math.random(1, n)
            local j = math.random(1, n)
            a[i], a[j] = a[j], a[i]
        end
        
        for i = 1, n do
            print(a[i])
        end
    end
end

local args = {...}
local n = tonumber(args[1])
local test_type = args[2]

if not n or not test_type then
    -- We don't print usage to stdout because it might be redirected to a test file
    -- But since this is a generator, if args are missing, it's a developer error.
    error("Usage: luau generator.luau -a <n> <type>")
end

generate_test(n, test_type)
