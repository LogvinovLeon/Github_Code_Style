/**
 * Created by hubert on 25.10.14.
 */
"use strict";

$(function () {

    $.get("https://students.mimuw.edu.pl/~ht335965/test.json")
        .done(function (result) {
            applyNotifications(result);
        })
        .fail(function (errmsg) {
            alert(errmsg);
        });
});

function applyNotifications(data) {
    console.log(data);
    var files = data.files;
    console.log(files);

    files.forEach(function (item) {
        item.notifications.forEach(function (notif) {
            console.log('filename', item.filename);
            console.log('notif', notif);
            console.log('.blob-code b[data-path="' + item.filename + '"][data-line="' + notif.line + '"]');
            var b = $('.blob-code b[data-path="' + item.filename + '"][data-line="' + notif.line + '"]');

            b.parent().parent()
                .addClass('cchub-notification')
                .addClass('cchub-' + notif.type);

            b.parent()
                .append(
                    '<div class="cchub-more-btn">' +
                        '<div class="cchub-icon"></div>' +
                    '</div>' +
                    '<div class="cchub-tooltip">' + notif.content + '</div>');
        });
    });
}