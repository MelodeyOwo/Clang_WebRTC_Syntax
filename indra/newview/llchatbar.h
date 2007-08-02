/** 
 * @file llchatbar.h
 * @brief LLChatBar class definition
 *
 * Copyright (c) 2002-$CurrentYear$, Linden Research, Inc.
 * $License$
 */

#ifndef LL_LLCHATBAR_H
#define LL_LLCHATBAR_H

#include "llpanel.h"
#include "llframetimer.h"
#include "llchat.h"

class LLLineEditor;
class LLMessageSystem;
class LLUICtrl;
class LLUUID;
class LLFrameTimer;
class LLChatBarGestureObserver;
class LLComboBox;

class LLChatBar
:	public LLPanel
{
public:
	// constructor for inline chat-bars (e.g. hosted in chat history window)
	LLChatBar(const std::string& name);
	LLChatBar(const std::string& name, const LLRect& rect);
	~LLChatBar();
	virtual BOOL postBuild();

	virtual void reshape(S32 width, S32 height, BOOL called_from_parent);
	virtual BOOL handleKeyHere(KEY key, MASK mask, BOOL called_from_parent);

	// Adjust buttons and input field for width
	void		layout();

	void		refresh();
	void		refreshGestures();

	// Move cursor into chat input field.
	void		setKeyboardFocus(BOOL b);

	// Ignore arrow keys for chat bar
	void		setIgnoreArrowKeys(BOOL b);

	BOOL		inputEditorHasFocus();
	LLString	getCurrentChat();

	// since chat bar logic is reused for chat history
	// gesture combo box might not be a direct child
	void		setGestureCombo(LLComboBox* combo);

	// Send a chat (after stripping /20foo channel chats).
	// "Animate" means the nodding animation for regular text.
	void		sendChatFromViewer(const LLWString &wtext, EChatType type, BOOL animate);
	void		sendChatFromViewer(const std::string &utf8text, EChatType type, BOOL animate);

	// If input of the form "/20foo" or "/20 foo", returns "foo" and channel 20.
	// Otherwise returns input and channel 0.
	LLWString stripChannelNumber(const LLWString &mesg, S32* channel);

	// callbacks
	static void	onClickSay( void* userdata );
	static void	onClickShout( void* userdata );

	static void	onTabClick( void* userdata );
	static void	onInputEditorKeystroke(LLLineEditor* caller, void* userdata);
	static void	onInputEditorFocusLost(LLUICtrl* caller,void* userdata);
	static void	onInputEditorGainFocus(LLUICtrl* caller,void* userdata);

	static void onCommitGesture(LLUICtrl* ctrl, void* data);

	static void startChat(void*);
	static void stopChat();

	/*virtual*/ void setVisible(BOOL visible);
protected:
	void sendChat(EChatType type);
	void updateChat();

protected:
	LLLineEditor*	mInputEditor;

	LLFrameTimer	mGestureLabelTimer;

	// Which non-zero channel did we last chat on?
	S32				mLastSpecialChatChannel;

	BOOL			mIsBuilt;
	BOOL			mDynamicLayout;
	LLComboBox*		mGestureCombo;

	LLChatBarGestureObserver* mObserver;
};

extern LLChatBar *gChatBar;

#endif
