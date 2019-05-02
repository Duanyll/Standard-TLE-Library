g++ example.cpp -o example.out
g++ example_std.cpp -o example_std.out
g++ example_dm.cpp -o example_dm.out
while true; do
    ./example_dm.out > example.in
    ./example_std.out < example.in > example_std.ans
    ./example.out < example.in > example.ans
    if diff example.ans example_std.ans; then
        printf "AC\n"
    else
        printf "WA\n"
        exit 0
    fi
done