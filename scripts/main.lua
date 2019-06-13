my_string = "lua works well in c++";
my_number = 42;

function Sum(a, b)
    return a + b
end


function Fib(n)
    a = 0
    b = 1
    i = 0
    sum = 0
    while i < n do
        sum = sum + a + b
        b = b + a
        a = b
        i = i + 1
    end
    return sum
end

print(Fib(10))
