// Generated from c:\Users\So&So\Desktop\Sophie\INSA_4IF\PLD_COMP\compilo\compiler\ifcc.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ifccParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		RETURN=10, CONST=11, TEXT=12, COMMENT=13, DIRECTIVE=14, WS=15;
	public static final int
		RULE_axiom = 0, RULE_prog = 1, RULE_l = 2, RULE_decl = 3, RULE_affect = 4, 
		RULE_var = 5, RULE_val = 6;
	public static final String[] ruleNames = {
		"axiom", "prog", "l", "decl", "affect", "var", "val"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'int'", "'main'", "'('", "')'", "'{'", "';'", "'}'", "','", "'='", 
		"'return'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, null, null, null, "RETURN", 
		"CONST", "TEXT", "COMMENT", "DIRECTIVE", "WS"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "ifcc.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ifccParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class AxiomContext extends ParserRuleContext {
		public ProgContext prog() {
			return getRuleContext(ProgContext.class,0);
		}
		public AxiomContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_axiom; }
	}

	public final AxiomContext axiom() throws RecognitionException {
		AxiomContext _localctx = new AxiomContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_axiom);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(14);
			prog();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ProgContext extends ParserRuleContext {
		public LContext l() {
			return getRuleContext(LContext.class,0);
		}
		public TerminalNode RETURN() { return getToken(ifccParser.RETURN, 0); }
		public ValContext val() {
			return getRuleContext(ValContext.class,0);
		}
		public ProgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_prog; }
	}

	public final ProgContext prog() throws RecognitionException {
		ProgContext _localctx = new ProgContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_prog);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(16);
			match(T__0);
			setState(17);
			match(T__1);
			setState(18);
			match(T__2);
			setState(19);
			match(T__3);
			setState(20);
			match(T__4);
			setState(21);
			l();
			setState(22);
			match(RETURN);
			setState(23);
			val();
			setState(24);
			match(T__5);
			setState(25);
			match(T__6);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LContext extends ParserRuleContext {
		public LContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_l; }
	 
		public LContext() { }
		public void copyFrom(LContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class LDeclContext extends LContext {
		public DeclContext decl() {
			return getRuleContext(DeclContext.class,0);
		}
		public LContext l() {
			return getRuleContext(LContext.class,0);
		}
		public LDeclContext(LContext ctx) { copyFrom(ctx); }
	}
	public static class LAffectContext extends LContext {
		public AffectContext affect() {
			return getRuleContext(AffectContext.class,0);
		}
		public LContext l() {
			return getRuleContext(LContext.class,0);
		}
		public LAffectContext(LContext ctx) { copyFrom(ctx); }
	}
	public static class LEpsilonContext extends LContext {
		public LEpsilonContext(LContext ctx) { copyFrom(ctx); }
	}

	public final LContext l() throws RecognitionException {
		LContext _localctx = new LContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_l);
		try {
			setState(36);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				_localctx = new LDeclContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(27);
				decl();
				setState(28);
				match(T__5);
				setState(29);
				l();
				}
				break;
			case 2:
				_localctx = new LAffectContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(31);
				affect();
				setState(32);
				match(T__5);
				setState(33);
				l();
				}
				break;
			case 3:
				_localctx = new LEpsilonContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DeclContext extends ParserRuleContext {
		public DeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_decl; }
	 
		public DeclContext() { }
		public void copyFrom(DeclContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class DeclMultipleContext extends DeclContext {
		public TerminalNode TEXT() { return getToken(ifccParser.TEXT, 0); }
		public DeclContext decl() {
			return getRuleContext(DeclContext.class,0);
		}
		public DeclMultipleContext(DeclContext ctx) { copyFrom(ctx); }
	}
	public static class DeclSimpleContext extends DeclContext {
		public TerminalNode TEXT() { return getToken(ifccParser.TEXT, 0); }
		public DeclSimpleContext(DeclContext ctx) { copyFrom(ctx); }
	}

	public final DeclContext decl() throws RecognitionException {
		DeclContext _localctx = new DeclContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_decl);
		try {
			setState(42);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				_localctx = new DeclMultipleContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(38);
				match(TEXT);
				setState(39);
				match(T__7);
				setState(40);
				decl();
				}
				break;
			case 2:
				_localctx = new DeclSimpleContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(41);
				match(TEXT);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AffectContext extends ParserRuleContext {
		public VarContext var() {
			return getRuleContext(VarContext.class,0);
		}
		public ValContext val() {
			return getRuleContext(ValContext.class,0);
		}
		public AffectContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_affect; }
	}

	public final AffectContext affect() throws RecognitionException {
		AffectContext _localctx = new AffectContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_affect);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(44);
			var();
			setState(45);
			match(T__8);
			setState(46);
			val();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VarContext extends ParserRuleContext {
		public VarContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_var; }
	 
		public VarContext() { }
		public void copyFrom(VarContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class VarTextContext extends VarContext {
		public TerminalNode TEXT() { return getToken(ifccParser.TEXT, 0); }
		public VarTextContext(VarContext ctx) { copyFrom(ctx); }
	}
	public static class VarDeclContext extends VarContext {
		public TerminalNode TEXT() { return getToken(ifccParser.TEXT, 0); }
		public VarDeclContext(VarContext ctx) { copyFrom(ctx); }
	}

	public final VarContext var() throws RecognitionException {
		VarContext _localctx = new VarContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_var);
		try {
			setState(51);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__0:
				_localctx = new VarDeclContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(48);
				match(T__0);
				setState(49);
				match(TEXT);
				}
				break;
			case TEXT:
				_localctx = new VarTextContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(50);
				match(TEXT);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ValContext extends ParserRuleContext {
		public ValContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_val; }
	 
		public ValContext() { }
		public void copyFrom(ValContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ValTextContext extends ValContext {
		public TerminalNode TEXT() { return getToken(ifccParser.TEXT, 0); }
		public ValTextContext(ValContext ctx) { copyFrom(ctx); }
	}
	public static class ValConstContext extends ValContext {
		public TerminalNode CONST() { return getToken(ifccParser.CONST, 0); }
		public ValConstContext(ValContext ctx) { copyFrom(ctx); }
	}

	public final ValContext val() throws RecognitionException {
		ValContext _localctx = new ValContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_val);
		try {
			setState(55);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case CONST:
				_localctx = new ValConstContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(53);
				match(CONST);
				}
				break;
			case TEXT:
				_localctx = new ValTextContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(54);
				match(TEXT);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\21<\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\3\2\3\2\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\5\4\'\n\4"+
		"\3\5\3\5\3\5\3\5\5\5-\n\5\3\6\3\6\3\6\3\6\3\7\3\7\3\7\5\7\66\n\7\3\b\3"+
		"\b\5\b:\n\b\3\b\2\2\t\2\4\6\b\n\f\16\2\2\29\2\20\3\2\2\2\4\22\3\2\2\2"+
		"\6&\3\2\2\2\b,\3\2\2\2\n.\3\2\2\2\f\65\3\2\2\2\169\3\2\2\2\20\21\5\4\3"+
		"\2\21\3\3\2\2\2\22\23\7\3\2\2\23\24\7\4\2\2\24\25\7\5\2\2\25\26\7\6\2"+
		"\2\26\27\7\7\2\2\27\30\5\6\4\2\30\31\7\f\2\2\31\32\5\16\b\2\32\33\7\b"+
		"\2\2\33\34\7\t\2\2\34\5\3\2\2\2\35\36\5\b\5\2\36\37\7\b\2\2\37 \5\6\4"+
		"\2 \'\3\2\2\2!\"\5\n\6\2\"#\7\b\2\2#$\5\6\4\2$\'\3\2\2\2%\'\3\2\2\2&\35"+
		"\3\2\2\2&!\3\2\2\2&%\3\2\2\2\'\7\3\2\2\2()\7\16\2\2)*\7\n\2\2*-\5\b\5"+
		"\2+-\7\16\2\2,(\3\2\2\2,+\3\2\2\2-\t\3\2\2\2./\5\f\7\2/\60\7\13\2\2\60"+
		"\61\5\16\b\2\61\13\3\2\2\2\62\63\7\3\2\2\63\66\7\16\2\2\64\66\7\16\2\2"+
		"\65\62\3\2\2\2\65\64\3\2\2\2\66\r\3\2\2\2\67:\7\r\2\28:\7\16\2\29\67\3"+
		"\2\2\298\3\2\2\2:\17\3\2\2\2\6&,\659";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}