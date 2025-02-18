﻿/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "api/api_common.h"
#include "chat_helpers/send_context_menu.h"
#include "data/data_poll.h"

class History;

namespace Ui {
class RpWidget;
class BoxContent;
class GenericBox;
} // namespace Ui

namespace Data {
class Folder;
class Session;
struct ForwardDraft;
} // namespace Data

namespace Dialogs {
class MainList;
struct EntryState;
} // namespace Dialogs

namespace Window {

class Controller;
class SessionController;
class SessionNavigation;

extern const char kOptionViewProfileInChatsListContextMenu[];

using PeerMenuCallback = Fn<QAction*(
	const QString &text,
	Fn<void()> handler,
	const style::icon *icon)>;

void FillDialogsEntryMenu(
	not_null<SessionController*> controller,
	Dialogs::EntryState request,
	const PeerMenuCallback &addAction);

void PeerMenuAddMuteAction(
	not_null<PeerData*> peer,
	const PeerMenuCallback &addAction);

void MenuAddMarkAsReadAllChatsAction(
	not_null<Data::Session*> data,
	const PeerMenuCallback &addAction);

void MenuAddMarkAsReadChatListAction(
	Fn<not_null<Dialogs::MainList*>()> &&list,
	const PeerMenuCallback &addAction);

void PeerMenuHidePinnedMessage(not_null<PeerData*> peer);
void PeerMenuUnhidePinnedMessage(not_null<PeerData*> peer);
void PeerMenuExportChat(not_null<PeerData*> peer);
void PeerMenuDeleteContact(not_null<UserData*> user);
void PeerMenuShareContactBox(
	not_null<Window::SessionNavigation*> navigation,
	not_null<UserData*> user);
void PeerMenuAddChannelMembers(
	not_null<Window::SessionNavigation*> navigation,
	not_null<ChannelData*> channel);
void PeerMenuCreatePoll(
	not_null<Window::SessionController*> controller,
	not_null<PeerData*> peer,
	MsgId replyToId = 0,
	PollData::Flags chosen = PollData::Flags(),
	PollData::Flags disabled = PollData::Flags(),
	Api::SendType sendType = Api::SendType::Normal,
	SendMenu::Type sendMenuType = SendMenu::Type::Scheduled);

struct ClearChat {
};
struct ClearReply {
	FullMsgId replyId;
};
void PeerMenuBlockUserBox(
	not_null<Ui::GenericBox*> box,
	not_null<Window::Controller*> window,
	not_null<PeerData*> peer,
	std::variant<v::null_t, bool> suggestReport,
	std::variant<v::null_t, ClearChat, ClearReply> suggestClear);
void PeerMenuUnblockUserWithBotRestart(not_null<UserData*> user);

void BlockSenderFromRepliesBox(
	not_null<Ui::GenericBox*> box,
	not_null<Window::SessionController*> controller,
	FullMsgId id);

void ToggleHistoryArchived(not_null<History*> history, bool archived);
Fn<void()> ClearHistoryHandler(not_null<PeerData*> peer);
Fn<void()> DeleteAndLeaveHandler(not_null<PeerData*> peer);

[[nodiscard]] Api::SendAction prepareSendAction(
		History *history, Api::SendOptions options);

QPointer<Ui::BoxContent> ShowNewForwardMessagesBox(
	not_null<Window::SessionNavigation*> navigation,
	MessageIdsList &&items,
	FnMut<void()> &&successCallback = nullptr);

QPointer<Ui::BoxContent> ShowForwardMessagesBox(
	not_null<Window::SessionNavigation*> navigation,
	MessageIdsList &&items,
	FnMut<void()> &&successCallback = nullptr);

QPointer<Ui::BoxContent> ShowForwardNoQuoteMessagesBox(
	not_null<Window::SessionNavigation*> navigation,
	MessageIdsList &&items,
	FnMut<void()> &&successCallback = nullptr);

QPointer<Ui::BoxContent> ShowSendNowMessagesBox(
	not_null<Window::SessionNavigation*> navigation,
	not_null<History*> history,
	MessageIdsList &&items,
	Fn<void()> &&successCallback = nullptr);

void ToggleMessagePinned(
	not_null<Window::SessionNavigation*> navigation,
	FullMsgId itemId,
	bool pin);
void HidePinnedBar(
	not_null<Window::SessionNavigation*> navigation,
	not_null<PeerData*> peer,
	Fn<void()> onHidden);
void UnpinAllMessages(
	not_null<Window::SessionNavigation*> navigation,
	not_null<History*> history);

} // namespace Window
