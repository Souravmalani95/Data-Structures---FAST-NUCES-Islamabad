#include "pch.h"
#include "Header.h"

TEST(ReadFileTest, TestOne) {
    const string expectedRead = "int fact(int n)\n{\n    \n    if (n > 0)\n    {\n        return n * fact(n-1);\n        \n    }\n    \n    return 1;\n    \n}\n\nvoid main()\n{\n    print Fact(3);\n    \n}\n";
    const string actualRead = readFile();
    EXPECT_EQ(expectedRead, actualRead);
}

TEST(RemoveLinesTest, TestOne) {
    const string expectedRead = "int fact(int n)\n{\n    if (n > 0)\n    {\n        return n * fact(n-1);\n    }\n    return 1;\n}\nvoid main()\n{\n    print Fact(3);\n}\n";
    const string actualCode = readFile();
    const string actualRead = removeLines(actualCode);
    EXPECT_EQ(expectedRead, actualRead);
}

TEST(PrependLinesTest, TestOne) {
    const string expectedRead = "C100    int fact(int n)\nC101    {\nC102        if (n > 0)\nC103        {\nC104            return n * fact(n-1);\nC105        }\nC106        return 1;\nC107    }\nC108    void main()\nC109    {\nC110        print Fact(3);\nC111    }\n";
    const string code = readFile();
    const string codeWithoutLines = removeLines(code);
    const string actualRead = prependLineAddress(codeWithoutLines);
    EXPECT_EQ(expectedRead, actualRead);
}

TEST(CheckIndentationTest, TestOne) {
    const string expectedOutput = "Indentation error detected";
    const string readCode = readFile("indentationCode.txt");
    const string actualOutput = checkIndentationErrors(readCode);
    EXPECT_EQ(expectedOutput, actualOutput);
}


TEST(CheckInfiniteLoopTest, TestOne) {
    const string expectedOutput = "Infinite loop detected";
    const string readCode = readFile("infiniteCode.txt");
    const string actualOutput = checkInfiniteLoop(readCode);
    EXPECT_EQ(expectedOutput, actualOutput);
}


TEST(RunTimeStackTest, TestOne) {
    const string expectedOutput = readFile("Program3Stack.txt");
    CreateRunTimeStack("Program3.txt", "Output_Program3Stack.txt");
    const string actualOutput = readFile("Output_Program3Stack.txt");
    EXPECT_EQ(expectedOutput, actualOutput);
}

TEST(InfixToPostfixTest, TestOne) {
    string expectedOutput = "ABC*EF-/+";
    string actualOutput = infixToPostfix("A+B*C/(E-F)");
    EXPECT_EQ(expectedOutput, actualOutput);
}


TEST(InfixToPostfixTest, TestTwo) {
   // string expectedOutput = "ABC*EF-/+";
    LinkedList<int> Variables;
    //Insertion is Done from the back on the basis of first-come, first-serve  
    Variables.insert(1); //Value for A 
    Variables.insert(2); //Value for B
    Variables.insert(3); //Value for C 
    Variables.insert(4); //Value for E 
    Variables.insert(5); //Value for F 
    int actualOutput = Solving_PostfixExpression("ABC*EF-/+", Variables);
    int expectedOutput = -5;
    EXPECT_EQ(expectedOutput, actualOutput);
}

TEST(TestCodeOutput, TestOne) {
    ExecuteCode("Program1.txt", "Output_Program1.txt");
    const string actualOutput = readFile("Output_Program1.txt");
    const string expectedOutput = "This is a recursive function.\nThis is a recursive function.\n";

    EXPECT_EQ(expectedOutput, actualOutput);
}

TEST(TestCodeOutput, TestTwo) {
    ExecuteCode("Program2.txt", "Output_Program2.txt");
    const string actualOutput = readFile("Output_Program2.txt");
    const string expectedOutput = "24\n";

    EXPECT_EQ(expectedOutput, actualOutput);
}

TEST(TestCodeOutput, TestThree) {
    ExecuteCode("Program3.txt", "Output_Program3.txt");
    const string actualOutput = readFile("Output_Program3.txt");
    const string expectedOutput = "6\n";

    EXPECT_EQ(expectedOutput, actualOutput);
}


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}