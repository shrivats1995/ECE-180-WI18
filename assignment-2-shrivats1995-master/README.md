# ECE-180 Assignment #2
Due: Feb 11, 11:15p (PST)

## Preface

We've spent the last few weeks covering the intricacies of C++ classes in considerable detail. Now it's your turn to create your first intermediate stand-alone class.

## Welcome to JobCo!

You've just started a new internship at JobCo, a chic software company in the heart of Silicon Valley that sells party balloons with integrated block-chain tracking. You've met your new manager, Chloe, who introduces you to the rest of the team. As you are wisked through the office, you race past a herd of zombies that are wandering aimlessly in the basement. "Oh my goodness", you say, in disbelief.  "Don't let them bother you", Chloe says smiling, "that's just the marketing department taking a lunch break". JobCo is going to be very interesting.

### Your FIRST Sprint Meeting

The next morning you get to sit in on your very first "Sprint Meeting" where the team discusses the work they're going to accomplish for the week. Each of the engineers talks briefly about their challenges and expected output. At last, all eyes drop onto you. Before panic seizes you, Chloes says, "Hey everyone, this is our new summer intern!". The team smiles knowingly, suggesting you may be in for more than you bargained for.  What happens next is mostly a blur. For one, you don't remember actually saying anything. But suddenly you realize that Chloe has tasked you with delivering some mission critical code, and FAST!  

### Your Team Makes a Decision

Just before the end of the standup meeting, Morris (a performance engineer) raises the topic of how slowly the application is performing. "Seriously", he says, "the app is running 5x slower today than it was a month ago". "What we need", he continues, "is someone to rewrite our string class to stop all the unnecessary memory allocations and performance problems."

"Great -- our new intern can build us a new string class this Sprint!", Chloe exclaims, never missing an opportunity. Sade, a UX designer on the team, says, "Hold on, why can't we just use the std::string class provided by the STL? Won't that be cheaper than building our own?"  Morris can barely contain himeself. "No!", he chides, "the STL is great in general, but it's way too big, and I just know we can build something smaller and faster!"

Sadly, no amount of arguing about re-inventing the wheel would stop Morris and Chloe from building their own string class. Welcome to Silicon Valley. :)

## Assignment Details

In this assignment, you are going to build a string class. String classes provide an object-oriented solution to managing character buffers in an application. Most modern applications have to manage strings to some degree, but for some applications, like word-processors and browsers, string management can have a tremendous impact on performance and memory management.

### Class interface (incomplete)

We have provided a starting point for your string class, in the SFString.hpp file.  It looks like this:

```

class SFString {
public:
  
  SFString();
  SFString(const SFString& aString);
  
  SFString&    operator=(const SFString& aString);
  
  operator const char*() const;
  
  char         operator[](int pos) const;

  SFString&    operator+=(const SFString &aString);
  
  bool         operator<(const SFString &aString);
  bool         operator<=(const SFString &aString);
  bool         operator>(const SFString &aString);
  bool         operator>=(const SFString &aString);
  bool         operator==(const SFString &aString);
  bool         operator!=(const SFString &aString);
  
  int          find(const SFString &aString, size_t offset=0);
  
  SFString&    insert(size_t aPos, const SFString &aString);
  SFString&    insert(size_t aPos, const char aChar);    
  SFString&    replace(size_t pos, size_t len, const SFString &aString);   
  SFString&    erase(size_t pos, size_t len);  
};

```

That's not too bad. One problem, though, is that the class also needs to support standard `char*` strings as well. 

### Part 1. -- Update the SFString class declaration in your .hpp file

In addition to the methods we have already provided for you, you need to add versions for most of these methods so users can use standard c-strings. For example, you will add a conversion constructor that accepts a const char*, like this:

```
  SFString(const char* aString);
```
Below, is an updated sample that indicates which methods you need to add to fully support const char*. Everywhere you see a comment that starts with "ADD..." below, you need to declare an additional member (method or operator) as indicated:

```

class SFString {
public:
  
  SFString();
  SFString(const SFString& aString);
  //ADD a conversion constructor that supports const char*...
  
  SFString&    operator=(const SFString& aString);
		//ADD "operator=" that supports const char*...
  
  operator const char*() const;
  char         operator[](int pos) const;

  SFString&    operator+=(const SFString &aString);
		//ADD "operator+=" that supports const char*...
  
  bool         operator<(const SFString &aString);
		//ADD "operator<" that supports const char*...
  
  bool         operator<=(const SFString &aString);
		//ADD "operator<=" that supports const char*...
  
  bool         operator>(const SFString &aString);
		//ADD "operator>" that supports const char*...
  
  bool         operator>=(const SFString &aString);
		//ADD "operator>=" that supports const char*...
  
  bool         operator==(const SFString &aString);
		//ADD "operator==" that supports const char*...
  
  bool         operator!=(const SFString &aString);
		//ADD "operator!=" that supports const char*...

  int          find(const SFString &aString, size_t offset=0);
		//ADD "find()" method that supports const char*...

  SFString&    insert(size_t aPos, const SFString &aString);
		//ADD "insert()" method that supports const char*...
		
  SFString&    replace(size_t pos, size_t len, const SFString &aString);
		//ADD "replace()" method that supports const char*...

  SFString&    erase(size_t pos, size_t len); 
		  
};

```

### Part 2. -- Implement your class (.cpp) 

Now that you have updated your header file (.hpp), take a look at the SFString.cpp file. You'll notice that is almost completely empty, as shown below.  You need to implement all of the SFString class functionality in your .cpp file. 

```
//
//  SFString.cpp
//  class_test
//
//  STUDENT: Your job here is to implement the string class functionality in this file...
//

#include "SFString.hpp"

```

**NOTE:** If you try to build (or make) this project, you'll find that you get a large number of errors and warnings.  That is to be expected.  The reason, is that we have provided a *very* incomplete set of files. It's up to you to complete the files (.hpp and .cpp) so that they compile (and obviously work).


### Part 3. -- Testing your SFString class implementation 

No self-respecting engineer would consider the job done unless they had also provided a complete set of tests to ensure that the solution worked as designed. Well, we've already provided a basic testing harness for you, contained in the SFStringTester files:

```
class SFStringTester {
public:
  static int runTests();
};
```

The self-testing harness is used in the main.cpp to initiate testing of your class, like this:

```
#include "SFStringTester.hpp"

int main(int argc, const char * argv[]) {
  SFStringTester::runTests();
  return 0;
}
```

Super easy, right? When the SFStringTester class runs your tests, it will output the results to `cout`. The test output makes it really easy to see which methods are working and which are not. Ok, there's just one thing to note. Our basic string testing class does a _pretty good_ job of testing your class, but you'll want to add some tests of your own.

### Part 4. -- Fill out the student.json file

Please make sure that you fill out your student.json file. We need your name, PID, email and the operating system you used for your work. For the operating system attribute, please specify "windows", "mac" or "linux". 

```
{
  "name"  : "Your Name",
  "pid"   : "Your StudentId",
  "email" : "Your Email",
  "os"    : "windows|mac|linux",
  "course": "ece180a"
}
```

### Part 5. -- Efficient Memory Management and Performance

See? Building a basic string class isn't all that hard. But making it run fast, and ensuring that uses memory efficiently takes considerably more effort. Finding the right balance between memory usage and performance can be a challenge.  In order to test your memory utilization and performance, you must write your own tests. To help you, we've added two extra functions in the SFStringTester class:

```
//run your own performance stress-tests here...
void runPerformanceTests() {
  
  //STUDENTS: ADD YOUR CODE HERE...
  
}

//run your own performance stress-tests here...
void runMemoryTests() {
  
  //STUDENTS: ADD YOUR CODE HERE...
  
}

```

## Grading

Your submission will be graded along four dimensions:

1. Suitability and correctness (40%)
2. Memory efficiency (25%)
3. Performance (25%)
4. Style and readability (10%)

As we explained earlier, in addition to passing the basic string tests (SFStringTest), your code will be measured for memory efficiency and performance. Our grading test harness will generate 1000's of strings and measure your memory usage. So make sure you test performance and memory efficiency carefully.


## Code Style Guide

This isn’t your first class on software or programming, and you’re probably wondering how we expect your code to be structured and formatted.  From the perspective of our auto-grader, structure and format are completely irrelevant. However, your instructors also will be viewing your code as well, so you would be wise to adhere to a few rules of thumb. 

### Format and Clarity

Your code should be formatted to be easily readable by anyone with more than 1 year of programming experience.  Here are some guidelines for things that matter:

- Avoid dense and complicated code
- Be consistent!  Choose a coding standard for yourself and stick with it
- Partition your logic into class methods as needed to maintain clarity
- Document your code with comments that clearly indicate what you’re doing at a high level

## Submitting Your Work

You’ll recall that your work is due by 11:15pm (PST).  We strongly recommend that you aim for 6p (PST) as to avoid the last minute mishaps that frequently occur when panic related to an impending deliverable begins, and we all tend to make silly mistakes.  

As we’ve said in lecture, you will turn your work in using GitHub. GitHub is an online code repository.  Managing code can be very confusing, but GitHub makes the process fairly easy. And the way we’re going to handle code in this class is even simpler still.  More on that later.

With that said, please understand that when you submit your work via GitHub, your changes are automatically timestamped. Meta data in the code repository makes it plainly obvious to humans and computers alike when your submission arrived.  This is worth mentioning, because the github timestamps on your submissions will be used to to arbitrate whether you turned your work in on time or not. 

Your homework will usually be auto-graded by “Vlad the Compiler” — otherwise known as our software-based auto-grader.  Vlad can be a bit harsh when it comes to scoring homework (see the syllabus), but he does have a somewhat casual relationship with deadlines.  During Grad-school, Vlad often spent spring-break in Cabo-San-Lucas where he learned to enjoy siestas.  Most nights, Vlad awakens from his last-afternoon siesta around midnight, to begin the process of grading your assignments. In other words, you can generally count on a 45 minute grace period for turning in your work. We strongly suggest that you do not try his patience.

**NOTE**: Please don't submit object or executable files with your submissions. Only check in text files (source, make, student.json, and so forth).  

## Caveats and Warnings

### You must make sure your code builds with our makefile

When you work on your assignments, many of you will create an IDE-based project. IDE’s will likely speed up your process, and give you additional tools, like an integrated debugger. 

It is important to note that Vlad-the-Compiler doesn’t use IDE projects. He uses makefiles to test and grade your homework.  Each of your assignments will include a makefile for this purpose. We strongly recommend that before you turn in your assignments, you attempt to build and run your code using this makefile.  

The files we provide for you by default in your assignment project folders will compile with the given makefile. They just won’t do much, until you add your own code to the solution. In general, you can feel free to change the files we provide you, and to add new files as necessary to solve the assigned problems. Note, however, that some of the files we provide for you have portions that are marked "DO NOT CHANGE".  We ask that you follow that advice carefully.

NOTE: It is **YOUR RESPONSIBILITY** to ensure your solution can be built correctly by the **make** command.

### Getting Help

You can talk with your peers about this problem. You can ask your instructors about this too. But you cannot use any other code for reference in solving these problems. If you're really stuck with an algorithm, join us in the programming dojo to get unblocked. It's really essential that you think about this challenge and work to solve it yourself.

## EXTRA Credit!

If you're feeling ambitious, you can earn extra credit if you complete this additional challenge.

### Adding support for operator+ 

Supporting operator+ may force you to learn a powerful new idiom in C++ on your own, before we discuss it in class. 
Let's take a look at how operator+ is used:

```
const char* thePrefix = "hello";
SFString theSuffix(" there");
SFString s3 = thePrefix + theSuffix;  //invoke operator+
```

In our sample code, we are concatenating a standard CString with an SFString. What makes this curious, is that CStrings don't offer methods of their own. Only objects (and sometimes classes) can do that. So how does this work? The secret is revealed when you realize that these are not members of a class, but rather, standalone functions. 

If you're up for the challenge, you can implement these methods:

```
SFString operator+(const SFString& lhs, const SFString& rhs);
SFString operator+(const SFString& lhs, const char* rhs);
SFString operator+(const char* lhs, const SFString& rhs);
```

If you choose to do this extra credit work, you must also enable the testing code so we know you are trying for the extra credit. Open the SFStringTester.cpp. Go to the bottom of the file in the runTests() method, and uncomment this line:

```
  //theErrors+=runExtraCreditTests();
```




