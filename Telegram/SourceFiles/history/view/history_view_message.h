/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "history/view/history_view_element.h"

class HistoryMessage;
struct HistoryMessageEdited;

namespace HistoryView {

// Special type of Component for the channel actions log.
struct LogEntryOriginal
	: public RuntimeComponent<LogEntryOriginal, Element> {
	LogEntryOriginal();
	LogEntryOriginal(LogEntryOriginal &&other);
	LogEntryOriginal &operator=(LogEntryOriginal &&other);
	~LogEntryOriginal();

	std::unique_ptr<HistoryWebPage> page;

};

class Message : public Element {
public:
	Message(not_null<HistoryMessage*> data, Context context);

	void draw(
		Painter &p,
		QRect clip,
		TextSelection selection,
		TimeMs ms) const override;
	bool hasPoint(QPoint point) const override;
	HistoryTextState getState(
		QPoint point,
		HistoryStateRequest request) const override;
	void updatePressed(QPoint point) override;
	void drawInfo(
		Painter &p,
		int right,
		int bottom,
		int width,
		bool selected,
		InfoDisplayType type) const override;
	bool pointInTime(
		int right,
		int bottom,
		QPoint point,
		InfoDisplayType type) const override;
	TextWithEntities selectedText(TextSelection selection) const override;
	TextSelection adjustSelection(
		TextSelection selection,
		TextSelectType type) const override;

	// hasFromPhoto() returns true even if we don't display the photo
	// but we need to skip a place at the left side for this photo
	bool hasFromPhoto() const override;
	bool displayFromPhoto() const override;
	bool hasFromName() const override;
	bool displayFromName() const override;
	bool displayForwardedFrom() const override;
	bool hasOutLayout() const override;
	bool drawBubble() const override;
	bool hasBubble() const override;
	bool hasFastReply() const override;
	bool displayFastReply() const override;
	bool displayRightAction() const override;
	void drawRightAction(
		Painter &p,
		int left,
		int top,
		int outerWidth) const override;
	ClickHandlerPtr rightActionLink() const override;
	bool displayEditedBadge() const override;
	QDateTime displayedEditDate() const override;
	int infoWidth() const override;

private:
	not_null<HistoryMessage*> message() const;

	void initLogEntryOriginal();
	void refreshEditedBadge();
	void fromNameUpdated(int width) const;

	[[nodiscard]] TextSelection skipTextSelection(
		TextSelection selection) const;
	[[nodiscard]] TextSelection unskipTextSelection(
		TextSelection selection) const;

	void paintFromName(Painter &p, QRect &trect, bool selected) const;
	void paintForwardedInfo(Painter &p, QRect &trect, bool selected) const;
	void paintReplyInfo(Painter &p, QRect &trect, bool selected) const;
	// this method draws "via @bot" if it is not painted in forwarded info or in from name
	void paintViaBotIdInfo(Painter &p, QRect &trect, bool selected) const;
	void paintText(Painter &p, QRect &trect, TextSelection selection) const;

	bool getStateFromName(
		QPoint point,
		QRect &trect,
		not_null<HistoryTextState*> outResult) const;
	bool getStateForwardedInfo(
		QPoint point,
		QRect &trect,
		not_null<HistoryTextState*> outResult,
		HistoryStateRequest request) const;
	bool getStateReplyInfo(
		QPoint point,
		QRect &trect,
		not_null<HistoryTextState*> outResult) const;
	bool getStateViaBotIdInfo(
		QPoint point,
		QRect &trect,
		not_null<HistoryTextState*> outResult) const;
	bool getStateText(
		QPoint point,
		QRect &trect,
		not_null<HistoryTextState*> outResult,
		HistoryStateRequest request) const;

	void updateMediaInBubbleState();
	QRect countGeometry() const;

	int resizeContentGetHeight(int newWidth);
	QSize performCountOptimalSize() override;
	QSize performCountCurrentSize(int newWidth) override;
	bool hasVisibleText() const override;

	bool displayFastShare() const;
	bool displayGoToOriginal() const;
	ClickHandlerPtr fastReplyLink() const;
	QDateTime displayedEditDate(bool hasViaBotOrInlineMarkup) const;
	const HistoryMessageEdited *displayedEditBadge() const;
	HistoryMessageEdited *displayedEditBadge();
	void initTime();
	int timeLeft() const;

	HistoryWebPage *logEntryOriginal() const;

	mutable ClickHandlerPtr _rightActionLink;
	mutable ClickHandlerPtr _fastReplyLink;

};

} // namespace HistoryView
