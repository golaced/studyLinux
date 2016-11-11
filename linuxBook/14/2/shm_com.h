#ifndef _SHM_COM_H__
#define _SHM_COM_H_

#define TEXT_SZ 2048
struct shared_use_st{
	int written_by_you;
	char some_text[TEXT_SZ];
};

#endif
