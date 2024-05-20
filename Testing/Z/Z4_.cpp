#include <iostream>
#include <utility>

template<typename T>
class MultiSet
{
public:
	MultiSet();
	MultiSet(const MultiSet &, int new_size = -1);
	MultiSet & operator = (MultiSet);
	~MultiSet();
	void clear();
	int size() const;
	T & operator [] (int index);
	const T & operator [] (int index) const;
	void add(const T &t);
	T del(int index);
private:
	T *arr;
	int real_size;
	int len;
};

template<typename T>
MultiSet<T>::MultiSet() : arr(nullptr), real_size(1), len(0)
{
	arr = new T[real_size];
}

template<typename T>
MultiSet<T>::MultiSet(const MultiSet &other, int new_size) : arr(nullptr),
		real_size(other.real_size), len(other.len)
{
	if (new_size <= real_size) {
		arr = new T[real_size];
	} else {
		arr = new T[new_size];
		real_size = new_size;
	}
	try {
		for (int i = 0; i < len; ++i) {
			arr[i] = other.arr[i];
		}
	} catch (std::exception &ex) {
		delete [] arr;
		throw;
	}
}

template<typename T>
MultiSet<T> &
MultiSet<T>::operator = (MultiSet other)
{
	std::swap(arr, other.arr);
	std::swap(real_size, other.real_size);
	std::swap(len, other.len);
	return *this;
}

template<typename T>
MultiSet<T>::~MultiSet()
{
	delete [] arr;
}

template<typename T>
void
MultiSet<T>::clear()
{
	len = 0;
}

template<typename T>
int
MultiSet<T>::size() const
{
	return len;
}

template<typename T>
T &
MultiSet<T>::operator [] (int index)
{
	if (index < 0 || index >= len) {
		throw std::exception();
	}
	return arr[index];
}

template<typename T>
const T &
MultiSet<T>::operator [] (int index) const
{
	if (index < 0 || index >= len) {
		throw std::exception();
	}
	return arr[index];
}

template<typename T>
void
MultiSet<T>::add(const T &t)
{
	if (len >= real_size) {
		MultiSet<T> new_multiset(*this, real_size * 2);
		new_multiset.arr[len] = t;
		++new_multiset.len;
		std::swap(arr, new_multiset.arr);
		std::swap(real_size, new_multiset.real_size);
		std::swap(len, new_multiset.len);
	} else {
		arr[len] = t;
		++len;
	}
}

template<typename T>
T
MultiSet<T>::del(int index)
{
	T tmp = (*this)[index];
	arr[index] = arr[len - 1];
	--len;
	return tmp;
}

class Component
{
public:
	Component();
	Component(const Component &) = delete;
	Component & operator = (const Component &) = delete;
	virtual ~Component();
	int count() const;
	Component & subcomponent(int);
	const Component & subcomponent(int) const;
	void add(Component &);
	friend std::ostream & operator << (std::ostream &, const Component &);
protected:
	MultiSet<Component *> multiset;
private:
	virtual const std::string & name() const = 0;
};

Component::Component() : multiset() {}

Component::~Component() {}

int
Component::count() const
{
	return multiset.size();
}

Component &
Component::subcomponent(int index)
{
	return *(multiset[index]);
}

const Component &
Component::subcomponent(int index) const
{
	return *(multiset[index]);
}

void
Component::add(Component &new_component)
{
	multiset.add(&new_component);
}

std::ostream &
operator << (std::ostream &stream, const Component &comp)
{
	stream << comp.name() << '(';
	for (int i = 0; i < comp.multiset.size(); ++i) {
		stream << *(comp.multiset[i]);
		if (i < comp.multiset.size() - 1) {
			stream << ", ";
		}
	}
	stream << ')';
	return stream;
}

class Box: public Component
{
public:
	Box(const std::string &);
	Box(const Box &);
	Box & operator = (const Box &);
	~Box();
private:
	const std::string & name() const;
	std::string str;
};

Box::Box(const std::string &s) : Component(), str(s) {}

Box::Box(const Box &other) : Component(), str(other.str) {}

Box &
Box::operator = (const Box &other)
{
	if (this != &other) {
		multiset.clear();
		str = other.str;
	}
	return *this;
}

Box::~Box() {}

const std::string &
Box::name() const
{
	return str;
}

#include <iostream>
#include <cctype>

struct Pair
{
	std::string name{};
	Component *component{};
};

enum Lexems
{
	NAME,
	OPEN,
	CLOSE,
	COMMA,
	END,
	ERR
};

struct Lex
{
	Lexems lex{};
	std::string name{};
};

class LexParser
{
public:
	LexParser(const std::string &);
	Lex get_lex();
private:
	std::string str;
	size_t pos;
};

LexParser::LexParser(const std::string &s) : str(s), pos(0) {}

Lex
LexParser::get_lex()
{
	while (pos < str.size() && isspace(str[pos])) {
		++pos;
	}
	if (pos >= str.size()) {
		return {END, ""};
	} else if (str[pos] == '(') {
		++pos;
		return {OPEN, ""};
	} else if (str[pos] == ')') {
		++pos;
		return {CLOSE, ""};
	} else if (str[pos] == ',') {
		++pos;
		return {COMMA, ""};
	} else if (isalpha(str[pos])) {
		std::string cur_name;
		cur_name.push_back(str[pos]);
		++pos;
		while (pos < str.size() && (isalpha(str[pos]) || isdigit(str[pos]))) {
			cur_name.push_back(str[pos]);
			++pos;
		}
		return {NAME, cur_name};
	} else {
		return {ERR, ""};
	}
}



class Parser
{
public:
	Parser();
	Parser(const Parser &) = delete;
	Parser & operator = (const Parser &) = delete;
	void parse(const std::string &, const MultiSet<Pair> &);
	Component * get_tree();
private:
	void S();
	void A();
	void D();
	void match(Lexems);
	void add();
	Lex c;
	LexParser *lex_parser;
	MultiSet<Pair> components;
	MultiSet<Component *> poliz;
};

Parser::Parser() : c(), lex_parser(), components(), poliz() {}

void
Parser::parse(const std::string &str, const MultiSet<Pair> &new_components)
{
	components = new_components;
	lex_parser = new LexParser(str);
	try {
		c = lex_parser->get_lex();
		S();
		if (c.lex != END) {
			throw std::exception();
		}
		delete lex_parser;
	} catch(std::exception &ex) {
		delete lex_parser;
		throw;
	}
}

void
Parser::match(Lexems x)
{
	if (c.lex == x) {
		c = lex_parser->get_lex();
	} else {
		throw std::exception();
	}
}

void
Parser::add()
{
	for (int i = 0; i < components.size(); ++i) {
		if (components[i].name == c.name) {
			poliz.add(components[i].component);
			components.del(i);
			return;
		}
	}
	throw std::exception();
}

void
Parser::S()
{
/*<*/
	poliz.clear();
		/*>*/
	A();
}

void
Parser::A()
{
	if (c.lex == NAME) {
	/*<*/
		add();
			/*>*/
		match(NAME);
		match(OPEN);
		D();
		match(CLOSE);
	} else {
		throw std::exception();
	}
}

void
Parser::D()
{
	if (c.lex == NAME) {
		A();
	/*<*/
		poliz.add(nullptr);
			/*>*/
		while (c.lex == COMMA) {
			match(COMMA);
			A();
		/*<*/
			poliz.add(nullptr);
				/*>*/
		}
	}
}

Component *
Parser::get_tree()
{
	MultiSet<Component *> stack;
	int pos_stack = 0;
	for (int i = 0; i < poliz.size(); ++i) {
		if (poliz[i] != nullptr) {
			stack.add(poliz[i]);
			++pos_stack;
		} else {
			--pos_stack;
			stack[pos_stack - 1]->add(*stack[pos_stack]);
			stack.del(pos_stack);
		}
	}
	return stack[0];
}

Component *
make_from_text(const std::string &text, const MultiSet<Pair> &components)
{
	Parser parser;
	parser.parse(text, components);
	return parser.get_tree();
}

int
main()
{
	for (std::string str; getline(std::cin, str); ) {
		MultiSet<Pair> components;
		for (char c = 'a'; c <= 'z'; ++c) {
			Box *b = new Box(std::string(1, c));
			Pair p{std::string(1, c), b};
			components.add(p);
		}
		try {
			Component * c = make_from_text(str, components);
			std::cout << *c << std::endl;
		} catch(...) {
			std::cout << "Exception" << std::endl;
		}
		for (int i = 'a' - 'a'; i <= 'z' - 'a'; ++i) {
			delete components[i].component;
		}
	}
	return 0;
}
