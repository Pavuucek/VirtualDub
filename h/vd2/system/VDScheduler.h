#ifndef f_VD2_SYSTEM_VDSCHEDULER_H
#define f_VD2_SYSTEM_VDSCHEDULER_H

#include <vd2/system/List.h>
#include <vd2/system/thread.h>
#include <vd2/system/VDAtomic.h>

class VDSchedulerNode;
class VDSignal;

class VDScheduler {
public:
	VDScheduler();
	~VDScheduler();

	void setSignal(VDSignal *);
	void setSchedulerNode(VDSchedulerNode *pSchedulerNode);

	bool Run();
	void Reschedule(VDSchedulerNode *);
	void Add(VDSchedulerNode *pNode);
	void Remove(VDSchedulerNode *pNode);

protected:
	void Repost(VDSchedulerNode *, bool);

	VDCriticalSection csScheduler;
	VDSignal *pWakeupSignal;
	VDSchedulerNode *pParentSchedulerNode;

	List2<VDSchedulerNode> listWaiting, listReady;
};

class VDSchedulerNode : public ListNode2<VDSchedulerNode> {
friend class VDScheduler;
public:
	int nPriority;

	virtual bool Service()=0;

	void Reschedule() { pScheduler->Reschedule(this); }
protected:
	VDScheduler *pScheduler;
	bool bRunning;
	bool bReschedule;
	bool bReady;
};

#endif
