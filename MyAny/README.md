As a developer
I want to have a class that can store single values of C++ fundamental type (except void and std::nullptr_t) and a function/method performs type-safe access to the conteined value.
so that I will be able use a single variable to store an int, then a double, then a bool etc.
Acceptance Criteria:
• The class should contain all type of constructors
• The class should contain all type of assignment operators
• The class should contain a method to destroy contained object
• The class should contain a method to swap two objects
• The class should contain a method returns the type of the contained value
• The function/method that extracts a value should provide type-safe access. If the requested type does not match to stored type exception should be thrown
Usage example:
…
AnyType anyType = 1;
anyType = true;
anyType = 1.7;

try
{
int storedValue = anyType.cast();
}
catch(exceptionType&)
{
//Bad cast exception
}
