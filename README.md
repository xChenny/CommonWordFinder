# Common Word Finder

## What this is

This is a utility that was made in C++ using support files that given a text file, it will find the words that are most commonly used in the text. This might be useful in the context of analyzing a text if you were interested in seeing what words are used more often in texts such as the Bible, or other long texts.

## How it works

This program was made in C++ using Red-Black-Trees to store instances of words as keys and the number of times that the word has been used as a value. When the user wants the top user-defined number of words the tree is rather fast at getting the words due to the self-balancing nature of redblack trees. The most oftenly used words are near the top of the tree whereas the least used words are towards the bottom.

## How to use it

Make sure that you have GCC and G++ installed

1. Go to whatever directory you wish to clone the repository.

    ```
    cd ~/Desktop/
    ```

2. Clone the repository:

    ```
    git clone https://github.com/xChenny/CommonWordFinder.git
    ```

3. Compile the code using the command:

    ```
    make
    ```

4. Run the project with whatever text file you have. bible.txt is included in the repo.

    ```
    ./commonwordfinder bible.txt
    ```
    By default the program will get the top 10 most used words. You can tell the program to get the top 25 most used words by typing in:

    ```
    ./commonwordfinder bible.txt 25
    ```
