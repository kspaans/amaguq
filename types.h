#ifndef __TYPES_H__
#define __TYPES_H__

struct amaguq;

enum a_type {
	ATOM,
	FIXNUM,
	BOOLEAN,
	CHARLIT,
	STRLIT,
	LIST,
	SYMBOL,
	QUOTE,
};

struct atom {
	virtual ~atom();

	virtual std::string print();
	virtual atom* eval();

	amaguq* interpreter;
	a_type atype;
};

struct fixnum : atom {
	fixnum(const std::string&);
	~fixnum();

	virtual std::string print();
	virtual atom* eval();

	int value;
};

struct boolean : atom {
	boolean(const std::string&);
	~boolean();

	virtual std::string print();
	virtual atom* eval();

	std::string str;
};

struct charlit : atom {
	charlit(const std::string&);
	~charlit();

	virtual std::string print();
	virtual atom* eval();

	std::string str;
};

struct strlit : atom {
	strlit(const std::string&);
	~strlit();

	virtual std::string print();
	virtual atom* eval();

	std::string str;
};

struct list : atom {
	list(atom*, atom*);
	~list();

	virtual std::string print();
	virtual atom* eval();

	atom* car;
	atom* cdr;
};

struct symbol : atom {
	symbol(const std::string&);
	~symbol();

	virtual std::string print();
	virtual atom* eval();

	std::string sym;
};

// TODO quotes shouldn't be a first-class, user-accessible type?
struct quote : atom {
	quote(atom*);
	~quote();

	virtual std::string print();
	virtual atom* eval();

	atom* q;
};

#endif
