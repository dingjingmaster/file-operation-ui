/*
 * Peony-Qt's Library
 *
 * Copyright (C) 2019, Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Yue Lan <lanyue@kylinos.cn>
 *
 */

#ifndef FILEOPERATIONERRORHANDLER_H
#define FILEOPERATIONERRORHANDLER_H

#include "file-operation.h"
#include "gerror-wrapper.h"
#include <QMetaType>

#include "peony-core_global.h"

#define ErrorHandlerIID "org.ukui.peony-qt.FileOperationErrorHandler"

namespace Peony {

class PEONYCORESHARED_EXPORT FileOperationErrorHandler : QObject {

    Q_OBJECT
    Q_PROPERTY(m_src_uri READ getSrcUri WRITE setSrcUri NOTIFY nameChanged)
    Q_PROPERTY(m_dest_uri READ getDestUri WRITE setDestUri NOTIFY nameChanged)
    Q_PROPERTY(m_error_string READ getErrorString WRITE setErrorString NOTIFY nameChanged)
public:
    enum ExceptionType
    {
        ET_GIO,
        ET_CUSTOM,
    };
    typedef struct _ResponseInfo
    {
        ExceptionType   error_type;
        int             error_code;
        QString         response_string;            // maybe i can use QMap to store result information
    } ResponseInfo;

    virtual ~FileOperationErrorHandler();
    virtual ResponseInfo* handleError(const QString &srcUri, const QString &destDirUri,
                                     const GErrorWrapperPtr &err, bool isCritical = false);

    virtual void setSrcUri (QString);
    virtual QString getSrcUri ();

protected:
    virtual ResponseInfo* packResult () = 0;

protected:
    QString m_src_uri;
    QString m_dest_uri;
    QString m_error_string;
};
}

Q_DECLARE_INTERFACE(Peony::FileOperationErrorHandler, ErrorHandlerIID)

#endif // FILEOPERATIONERRORHANDLER_H
