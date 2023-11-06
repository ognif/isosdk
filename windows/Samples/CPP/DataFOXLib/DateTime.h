#ifndef _DATETIME_H_
#define _DATETIME_H_

#define DECLARE_DATE_TIME_CONTROLS(name)	\
	FXSpinner * m_sp##name##Year;			\
	FXSpinner * m_sp##name##Month;			\
	FXSpinner * m_sp##name##Day;			\
	FXComboBox * m_cb##name##Hour;			\
	FXComboBox * m_cb##name##Minute	

#define DEFINE_COMBO(name, parent, lo, hi, val)							\
		name = new FXComboBox(parent, 2,				0,				\
		0						, COMBOBOX_STATIC | FRAME_SUNKEN  | FRAME_THICK);	\
		for(int i = lo; i < hi; ++i)									\
		{																\
			FXString str;												\
			str.format("%02d", i);										\
			name->appendItem(str);					\
		}																\
		name->setCurrentItem(val);										\
		name->setNumVisible(10);

#define DEFINE_DATE_TIME_CONTROLS(name, parent, sync_id)	\
	m_sp##name##Year = new FXSpinner(parent, 4, this, sync_id,SPIN_CYCLIC | FRAME_SUNKEN | FRAME_THICK);			\
	new FXLabel(parent,".");																							\
	m_sp##name##Month = new FXSpinner(parent, 2, this, sync_id,SPIN_CYCLIC | FRAME_SUNKEN | FRAME_THICK);			\
	new FXLabel(parent,".");																							\
	m_sp##name##Day = new FXSpinner(parent, 2,0,0,SPIN_CYCLIC | FRAME_SUNKEN | FRAME_THICK);											\
	new FXLabel(parent," - ");																							\
	m_sp##name##Year->setRange(1900, 2100);																				\
	m_sp##name##Year->setValue(2008);																					\
	m_sp##name##Month->setRange(1, 12);																					\
	m_sp##name##Month->setValue(12);																					\
	m_sp##name##Day->setRange(1, 31);																					\
	m_sp##name##Day->setValue(31);																						\
	DEFINE_COMBO(m_cb##name##Hour, parent, 0, 24, 16)																	\
	new FXLabel(parent,"::");																							\
	DEFINE_COMBO(m_cb##name##Minute, parent, 0, 60, 30)												

#define SET_DATE_TIME(name, dateTime)					\
	m_sp##name##Year->setValue(dateTime.nYear+1900);	\
	m_sp##name##Month->setValue(dateTime.nMonth);		\
	m_sp##name##Day->setValue(dateTime.nDay);			\
	m_cb##name##Hour->setCurrentItem(dateTime.nHour);	\
	m_cb##name##Minute->setCurrentItem(dateTime.nMinute)	

#define SYNC_DATE_TIME(name)\
{																					\
	FXDate date(m_sp##name##Year->getValue(), m_sp##name##Month->getValue(), 1);	\
	int val = m_sp##name##Day->getValue();											\
	m_sp##name##Day->setRange(0, date.daysInMonth());								\
	if(val > date.daysInMonth())													\
	{																				\
		m_sp##name##Day->setValue(date.daysInMonth());								\
	}																				\
}

#define COPY_DATE_TIME(name, dateTime)							\
	dateTime.nYear = m_sp##name##Year->getValue() - 1900;		\
	dateTime.nMonth = m_sp##name##Month->getValue();			\
	dateTime.nDay = m_sp##name##Day->getValue();				\
	dateTime.nHour = m_cb##name##Hour->getCurrentItem();		\
	dateTime.nMinute = m_cb##name##Minute->getCurrentItem();	\
	dateTime.nSecond = 0

#endif // _DATETIME_H_
